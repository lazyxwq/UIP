/**
 * \addtogroup uip
 * @{
 */

/**
 * \defgroup uiparp uIP Address Resolution Protocol
 * @{
 *
 * The Address Resolution Protocol ARP is used for mapping between IP
 * addresses and link level addresses such as the Ethernet MAC
 * addresses. ARP uses broadcast queries to ask for the link level
 * address of a known IP address and the host which is configured with
 * the IP address for which the query was meant, will respond with its
 * link level address.
 *
 * \note This ARP implementation only supports Ethernet.
 */
 
/**
 * \file
 * Implementation of the ARP Address Resolution Protocol.
 * \author Adam Dunkels <adam@dunkels.com>
 *
 */

/*
 * Copyright (c) 2001-2003, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: uip_arp.c,v 1.8 2006/06/02 23:36:21 adam Exp $
 *
 */


#include "uip_arp.h"

#include <string.h>

struct arp_hdr {
  struct uip_eth_hdr ethhdr;
  u16_t hwtype;
  u16_t protocol;
  u8_t hwlen;
  u8_t protolen;
  u16_t opcode;
  struct uip_eth_addr shwaddr;
  u16_t sipaddr[2];
  struct uip_eth_addr dhwaddr;
  u16_t dipaddr[2];
};

struct ethip_hdr {
  struct uip_eth_hdr ethhdr;
  /* IP header. IP报头结构体*/
  u8_t vhl,
    tos,
    len[2],
    ipid[2],
    ipoffset[2],
    ttl,
    proto;
  u16_t ipchksum;
  u16_t srcipaddr[2],
    destipaddr[2];
};

#define ARP_REQUEST 1
#define ARP_REPLY   2

#define ARP_HWTYPE_ETH 1

struct arp_entry {
  u16_t ipaddr[2];
  struct uip_eth_addr ethaddr;
  u8_t time;
};

static const struct uip_eth_addr broadcast_ethaddr =
  {{0xff,0xff,0xff,0xff,0xff,0xff}};
static const u16_t broadcast_ipaddr[2] = {0xffff,0xffff};

static struct arp_entry arp_table[UIP_ARPTAB_SIZE];
static u16_t ipaddr[2];
static u8_t i, c;

static u8_t arptime;
static u8_t tmpage;

#define BUF   ((struct arp_hdr *)&uip_buf[0])
#define IPBUF ((struct ethip_hdr *)&uip_buf[0])
/*-----------------------------------------------------------------------------------*/
/**
 * Initialize the ARP module.
 * 初始化ARP模块
 */
/*-----------------------------------------------------------------------------------*/
void
uip_arp_init(void)
{
  for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
    memset(arp_table[i].ipaddr, 0, 4);
  }
}
/*-----------------------------------------------------------------------------------*/
/**
 * Periodic ARP processing function.
 * 定期ARP处理函数。
 * This function performs periodic timer processing in the ARP module
 * and should be called at regular intervals. The recommended interval
 * is 10 seconds between the calls.
 * 这个函数在固定的时间间隔中被调用，用于执行ARP模块周期定时处理功能。两次函数调用的间隔时间推荐为10s。
 */
/*-----------------------------------------------------------------------------------*/
void
uip_arp_timer(void)
{
  struct arp_entry *tabptr;
  
  ++arptime;
  for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
    tabptr = &arp_table[i];
    if((tabptr->ipaddr[0] | tabptr->ipaddr[1]) != 0 &&
       arptime - tabptr->time >= UIP_ARP_MAXAGE) {
      memset(tabptr->ipaddr, 0, 4);
    }
  }

}
/*-----------------------------------------------------------------------------------*/
static void
uip_arp_update(u16_t *ipaddr, struct uip_eth_addr *ethaddr)
{
  register struct arp_entry *tabptr;
  /* Walk through the ARP mapping table and try to find an entry to
     update. If none is found, the IP -> MAC address mapping is
     inserted in the ARP table. 遍历ARP映射表并试图更新表格 。如果没有更新，IP->MAC地址映射会插入ARP表中*/
  for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {

    tabptr = &arp_table[i];
    /* Only check those entries that are actually in use.
	   仅检查实际使用到的条目 */
    if(tabptr->ipaddr[0] != 0 &&
       tabptr->ipaddr[1] != 0) {

      /* Check if the source IP address of the incoming packet matches
         the IP address in this ARP table entry. 
		 检查传入的报文的源IP地址和ARP表项中的IP地址条目是否匹配。*/
      if(ipaddr[0] == tabptr->ipaddr[0] &&
	 ipaddr[1] == tabptr->ipaddr[1]) {
	 
	/* An old entry found, update this and return. 找到一个旧的条目，更新并返回它。*/
	memcpy(tabptr->ethaddr.addr, ethaddr->addr, 6);
	tabptr->time = arptime;

	return;
      }
    }
  }

  /* If we get here, no existing ARP table entry was found, so we
     create one. 如果执行到这里，ARP表项找不到，就需要新建一个。*/

  /* First, we try to find an unused entry in the ARP table. 
  	 首先，我们试图找到一个不使用了的ARP表项。*/
  for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
    tabptr = &arp_table[i];
    if(tabptr->ipaddr[0] == 0 &&
       tabptr->ipaddr[1] == 0) {
      break;
    }
  }

  /* If no unused entry is found, we try to find the oldest entry and
     throw it away. 如果找不到无用的ARP表项，试图找到一个最老的表项并丢弃他。*/
  if(i == UIP_ARPTAB_SIZE) {
    tmpage = 0;
    c = 0;
    for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
      tabptr = &arp_table[i];
      if(arptime - tabptr->time > tmpage) {
	tmpage = arptime - tabptr->time;
	c = i;
      }
    }
    i = c;
    tabptr = &arp_table[i];
  }

  /* Now, i is the ARP table entry which we will fill with the new
     information. 现在i代表ARP第【i】个表项，给他填充新的信息。*/
  memcpy(tabptr->ipaddr, ipaddr, 4);
  memcpy(tabptr->ethaddr.addr, ethaddr->addr, 6);
  tabptr->time = arptime;
}
/*-----------------------------------------------------------------------------------*/
/**
 * ARP processing for incoming IP packets 传入的IP数据包的处理函数
 *
 * This function should be called by the device driver when an IP
 * packet has been received. The function will check if the address is
 * in the ARP cache, and if so the ARP cache entry will be
 * refreshed. If no ARP cache entry was found, a new one is created.
 	当接收到IP数据包时通过设备驱动调用这个函数。这个函数会检查IP地址是否在ARP缓存中，
	如果在，就更新这项，如果不在则为这个IP地址创建一个ARP表项。
 *
 * This function expects an IP packet with a prepended Ethernet header
 * in the uip_buf[] buffer, and the length of the packet in the global
 * variable uip_len.
 	这个函数为在uip_buf缓冲区的IP报文添加一个以太网报文头。修改后更新报文的长度变量
 */
/*-----------------------------------------------------------------------------------*/
#if 0
void
uip_arp_ipin(void)
{
  uip_len -= sizeof(struct uip_eth_hdr);
	
  /* Only insert/update an entry if the source IP address of the
     incoming IP packet comes from a host on the local network. 
	 仅为传入的是来自本地网络的IP报文，在ARP表项中更新和插入该报文的源IP地址。*/
  if((IPBUF->srcipaddr[0] & uip_netmask[0]) !=
     (uip_hostaddr[0] & uip_netmask[0])) {
    return;
  }
  if((IPBUF->srcipaddr[1] & uip_netmask[1]) !=
     (uip_hostaddr[1] & uip_netmask[1])) {
    return;
  }
  uip_arp_update(IPBUF->srcipaddr, &(IPBUF->ethhdr.src));
  
  return;
}
#endif /* 0 */
/*-----------------------------------------------------------------------------------*/
/**
 * ARP processing for incoming ARP packets.	传入ARP报文的处理方法
 *
 * This function should be called by the device driver when an ARP
 * packet has been received. The function will act differently
 * depending on the ARP packet type: if it is a reply for a request
 * that we previously sent out, the ARP cache will be filled in with
 * the values from the ARP reply. If the incoming ARP packet is an ARP
 * request for our IP address, an ARP reply packet is created and put
 * into the uip_buf[] buffer.
 	当接收到一个ARP报文时通过设备驱动调用这个函数。这个函数依靠不同的ARP报文类型执行不同的操作：
	如果该报文是我们先前发送的请求报文的回复报文，ARP缓存将会填入回复报文的值。如果传入的ARP报文
	是一个请求我们IP地址的请求报文，我们需要创建一个回复报文放如uip_buf缓冲区中。
 *
 * When the function returns, the value of the global variable uip_len
 * indicates whether the device driver should send out a packet or
 * not. If uip_len is zero, no packet should be sent. If uip_len is
 * non-zero, it contains the length of the outbound packet that is
 * present in the uip_buf[] buffer.
 	当函数返回时，全局变量uip_len的值意味着设备驱动是否发送了报文。
	如果uip_len为零则没有发送报文，如果不为零则表示发送了一个报文，该值为刚发送的报文的长度。
 *
 * This function expects an ARP packet with a prepended Ethernet
 * header in the uip_buf[] buffer, and the length of the packet in the
 * global variable uip_len.
 	这个函数需要为在存放在uip_buf缓冲区中的ARP报文添加一个前置的以太网报文头，并更新该报文的长度变量
 */
/*-----------------------------------------------------------------------------------*/
void
uip_arp_arpin(void)
{
  
  if(uip_len < sizeof(struct arp_hdr)) {
    uip_len = 0;
    return;
  }
  uip_len = 0;
  
  switch(BUF->opcode) {
  case HTONS(ARP_REQUEST):
    /* ARP request. If it asked for our address, we send out a
       reply. 如果是ARP请求报文，如果对方请求得到我们的IP地址，将发给对方一个回复。*/
    if(uip_ipaddr_cmp(BUF->dipaddr, uip_hostaddr)) {
      /* First, we register the one who made the request in our ARP
	 table, since it is likely that we will do more communication
	 with this host in the future. 
	 	首先，我们需要在ARP表中添加这个发送请求报文的主机地址，因为该主机以后
		很有可能会与我们做更多的交流。*/
      uip_arp_update(BUF->sipaddr, &BUF->shwaddr);
      
      /* The reply opcode is 2. 回复操作码2*/
      BUF->opcode = HTONS(2);

      memcpy(BUF->dhwaddr.addr, BUF->shwaddr.addr, 6);
      memcpy(BUF->shwaddr.addr, uip_ethaddr.addr, 6);
      memcpy(BUF->ethhdr.src.addr, uip_ethaddr.addr, 6);
      memcpy(BUF->ethhdr.dest.addr, BUF->dhwaddr.addr, 6);
      
      BUF->dipaddr[0] = BUF->sipaddr[0];
      BUF->dipaddr[1] = BUF->sipaddr[1];
      BUF->sipaddr[0] = uip_hostaddr[0];
      BUF->sipaddr[1] = uip_hostaddr[1];

      BUF->ethhdr.type = HTONS(UIP_ETHTYPE_ARP);
      uip_len = sizeof(struct arp_hdr);
    }
    break;
  case HTONS(ARP_REPLY):
    /* ARP reply. We insert or update the ARP table if it was meant
       for us. 如果收到的是ARP回复报文，如果该报文是发送给我们的，我们需要更新或插入ARP表*/
    if(uip_ipaddr_cmp(BUF->dipaddr, uip_hostaddr)) {
      uip_arp_update(BUF->sipaddr, &BUF->shwaddr);
    }
    break;
  }

  return;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Prepend Ethernet header to an outbound IP packet and see if we need
 * to send out an ARP request.
 *	如果我们需要发送一个ARP请求报文，需要在要发送的IP报文前头添加一个以太网报文头。

 * This function should be called before sending out an IP packet. The
 * function checks the destination IP address of the IP packet to see
 * what Ethernet MAC address that should be used as a destination MAC
 * address on the Ethernet.
 *	这个函数在发送IP报文之前调用。该函数检查要发送的IP数据包的目的IP地址以及
 	查看发送这个报文的以太网MAC地址

 * If the destination IP address is in the local network (determined
 * by logical ANDing of netmask and our IP address), the function
 * checks the ARP cache to see if an entry for the destination IP
 * address is found. If so, an Ethernet header is prepended and the
 * function returns. If no ARP cache entry is found for the
 * destination IP address, the packet in the uip_buf[] is replaced by
 * an ARP request packet for the IP address. The IP packet is dropped
 * and it is assumed that they higher level protocols (e.g., TCP)
 * eventually will retransmit the dropped packet.
 * 	如果该目的IP地址在本网段内（通过掩码与本机IP地址逻辑与判断），该函数检查
 	ARP缓存中是否能找到该目的IP地址条目。如果找到，准备一个以太网头，然后返回函数。
	如果找不到，存放在uip_buf中的报文里的目的IP地址会被ARP请求报文中的IP地址替代。
	假定这个报文时由更高级的协议创建的，它将会被丢弃，最终会重传这个被丢弃的报文。

 * If the destination IP address is not on the local network, the IP				
 * address of the default router is used instead.
 *	如果这个目的IP地址不再本网段内，目的IP地址将会被默认路由器地址取代。

 * When the function returns, a packet is present in the uip_buf[]
 * buffer, and the length of the packet is in the global variable
 * uip_len.
 	当函数返回时，生成的数据包将存放在uip_buf缓冲区中，报文长度放在uip_len里。
 */
/*-----------------------------------------------------------------------------------*/
void
uip_arp_out(void)
{
  struct arp_entry *tabptr;
  
  /* Find the destination IP address in the ARP table and construct
     the Ethernet header. If the destination IP addres isn't on the
     local network, we use the default router's IP address instead.
	 	从ARP表中找到该目的IP地址，并为他构造一个以太网报文头。如果这个目的IP地址
		不在本网段中，我们会使用默认路由器的地址取代该地址。
     If not ARP table entry is found, we overwrite the original IP
     packet with an ARP request for the IP address. 
	 	如果在ARP表中找不到该目的IP地址项，我们会用ARP请求报文的IP地址
		覆盖原先的IP地址。*/

  /* First check if destination is a local broadcast. 
  		首先，检查目的地址是否是本地广播地址*/
  if(uip_ipaddr_cmp(IPBUF->destipaddr, broadcast_ipaddr)) {
    memcpy(IPBUF->ethhdr.dest.addr, broadcast_ethaddr.addr, 6);
  } else {
    /* Check if the destination address is on the local network. 
		检查目的地址是否在本网段中*/
    if(!uip_ipaddr_maskcmp(IPBUF->destipaddr, uip_hostaddr, uip_netmask)) {
      /* Destination address was not on the local network, so we need to
	 use the default router's IP address instead of the destination
	 address when determining the MAC address. 
	 		目的地址不再本网段中，所以我们需要使用默认路由地址答题这个目的地址。
			*/
      uip_ipaddr_copy(ipaddr, uip_draddr);
    } else {
      /* Else, we use the destination IP address. 否则我们使用目的IP地址*/
      uip_ipaddr_copy(ipaddr, IPBUF->destipaddr);
    }
      
    for(i = 0; i < UIP_ARPTAB_SIZE; ++i) {
      tabptr = &arp_table[i];
      if(uip_ipaddr_cmp(ipaddr, tabptr->ipaddr)) {
	break;
      }
    }

    if(i == UIP_ARPTAB_SIZE) {
      /* The destination address was not in our ARP table, so we
	 overwrite the IP packet with an ARP request. 目的IP地址不再ARP表中，
	 所以我们使用ARP请求报文的地址覆盖要发送的IP报文的地址*/

      memset(BUF->ethhdr.dest.addr, 0xff, 6);
      memset(BUF->dhwaddr.addr, 0x00, 6);
      memcpy(BUF->ethhdr.src.addr, uip_ethaddr.addr, 6);
      memcpy(BUF->shwaddr.addr, uip_ethaddr.addr, 6);
    
      uip_ipaddr_copy(BUF->dipaddr, ipaddr);
      uip_ipaddr_copy(BUF->sipaddr, uip_hostaddr);
      BUF->opcode = HTONS(ARP_REQUEST); /* ARP request. */
      BUF->hwtype = HTONS(ARP_HWTYPE_ETH);
      BUF->protocol = HTONS(UIP_ETHTYPE_IP);
      BUF->hwlen = 6;
      BUF->protolen = 4;
      BUF->ethhdr.type = HTONS(UIP_ETHTYPE_ARP);

      uip_appdata = &uip_buf[UIP_TCPIP_HLEN + UIP_LLH_LEN];
    
      uip_len = sizeof(struct arp_hdr);
      return;
    }

    /* Build an ethernet header. 创建一个以太网报文头*/
    memcpy(IPBUF->ethhdr.dest.addr, tabptr->ethaddr.addr, 6);
  }
  memcpy(IPBUF->ethhdr.src.addr, uip_ethaddr.addr, 6);
  
  IPBUF->ethhdr.type = HTONS(UIP_ETHTYPE_IP);

  uip_len += sizeof(struct uip_eth_hdr);
}
/*-----------------------------------------------------------------------------------*/

/** @} */
/** @} */
