/**
 * \addtogroup uip
 * @{
 */

/**
 * \file
 * Header file for the uIP TCP/IP stack.
 * \author Adam Dunkels <adam@dunkels.com>
 *
 * The uIP TCP/IP stack header file contains definitions for a number
 * of C macros that are used by uIP programs as well as internal uIP
 * structures, TCP/IP header structures and function declarations.
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
 * $Id: uip.h,v 1.40 2006/06/08 07:12:07 adam Exp $
 *
 */

#ifndef __UIP_H__
#define __UIP_H__

#include "uipopt.h"

/**
 * Repressentation of an IP address.  表示一个IP地址
 *
 */
typedef u16_t uip_ip4addr_t[2];
typedef u16_t uip_ip6addr_t[8];
#if UIP_CONF_IPV6
typedef uip_ip6addr_t uip_ipaddr_t;
#else /* UIP_CONF_IPV6 */
typedef uip_ip4addr_t uip_ipaddr_t;
#endif /* UIP_CONF_IPV6 */

/*---------------------------------------------------------------------------*/
/* First, the functions that should be called from the
 * system. Initialization, the periodic timer and incoming packets are
 * handled by the following three functions.
 	首先，在系统中调用这个函数。初始化、周期定时器和传包是由以下三个函数处理。
 */

/**
 * \defgroup uipconffunc uIP configuration functions
 * @{
 *
 * The uIP configuration functions are used for setting run-time
 * parameters in uIP such as IP addresses.
 	uip配置函数用于在程序运行时配置uip参数，比如配置IP地址
 */

/**
 * Set the IP address of this host.	设置这个主机的IP地址
 *
 * The IP address is represented as a 4-byte array where the first
 * octet of the IP address is put in the first member of the 4-byte
 * array.
 *
 * Example:
 \code

 uip_ipaddr_t addr;

 uip_ipaddr(&addr, 192,168,1,2);
 uip_sethostaddr(&addr);

 \endcode
 * \param addr A pointer to an IP address of type uip_ipaddr_t;
 *
 * \sa uip_ipaddr()
 *
 * \hideinitializer
 */
#define uip_sethostaddr(addr) uip_ipaddr_copy(uip_hostaddr, (addr))

/**
 * Get the IP address of this host. 得到该主机的IP地址
 *
 * The IP address is represented as a 4-byte array where the first
 * octet of the IP address is put in the first member of the 4-byte
 * array.
 *
 * Example:
 \code
 uip_ipaddr_t hostaddr;

 uip_gethostaddr(&hostaddr);
 \endcode
 * \param addr A pointer to a uip_ipaddr_t variable that will be
 * filled in with the currently configured IP address.
 *
 * \hideinitializer
 */
#define uip_gethostaddr(addr) uip_ipaddr_copy((addr), uip_hostaddr)

/**
 * Set the default router's IP address.	 设置默认路由器的IP地址
 *
 * \param addr A pointer to a uip_ipaddr_t variable containing the IP
 * address of the default router.
 *
 * \sa uip_ipaddr()
 *
 * \hideinitializer
 */
#define uip_setdraddr(addr) uip_ipaddr_copy(uip_draddr, (addr))

/**
 * Set the netmask.	设置掩码
 *
 * \param addr A pointer to a uip_ipaddr_t variable containing the IP
 * address of the netmask.
 *
 * \sa uip_ipaddr()
 *
 * \hideinitializer
 */
#define uip_setnetmask(addr) uip_ipaddr_copy(uip_netmask, (addr))


/**
 * Get the default router's IP address.	得到默认路由器的IP地址
 *
 * \param addr A pointer to a uip_ipaddr_t variable that will be
 * filled in with the IP address of the default router.
 *
 * \hideinitializer
 */
#define uip_getdraddr(addr) uip_ipaddr_copy((addr), uip_draddr)

/**
 * Get the netmask.	的到掩码
 *
 * \param addr A pointer to a uip_ipaddr_t variable that will be
 * filled in with the value of the netmask.
 *
 * \hideinitializer
 */
#define uip_getnetmask(addr) uip_ipaddr_copy((addr), uip_netmask)

/** @} */

/**
 * \defgroup uipinit uIP initialization functions uip初始化函数
 * @{
 *
 * The uIP initialization functions are used for booting uIP.
	这个初始化函数用于启动UIP协议栈
 */

/**
 * uIP initialization function.	UIP初始化函数
 *
 * This function should be called at boot up to initilize the uIP
 * TCP/IP stack.
 	这个在启动的时候被调用用来初始化TCP/IP协议栈
 */
void uip_init(void);

/**
 * uIP initialization function.
 *
 * This function may be used at boot time to set the initial ip_id.
 	这个函数用来在启动时设置初始ip_id
 */
void uip_setipid(u16_t id);

/** @} */

/**
 * \defgroup uipdevfunc uIP device driver functions	UIP设备驱动函数
 * @{
 *
 * These functions are used by a network device driver for interacting
 * with uIP.
 	这个函数被用来使网络设备驱动与UIP进行交互。
 */

/**
 * Process an incoming packet. 处理一个传入的报文
 *
 * This function should be called when the device driver has received
 * a packet from the network. The packet from the device driver must
 * be present in the uip_buf buffer, and the length of the packet
 * should be placed in the uip_len variable.
 	当设备驱动从网络上接收到一个报文后调用这个函数，。接收到的报文必须放在uip_buf缓冲区中，
	报文长度需要放在uip_len变量中
 *
 * When the function returns, there may be an outbound packet placed
 * in the uip_buf packet buffer. If so, the uip_len variable is set to
 * the length of the packet. If no packet is to be sent out, the
 * uip_len variable is set to 0.
 	当函数返回时，可能需要发送的报文会存放在uip_buf缓冲区中，因此uip_len长度也需要
	修改成发送报文的长度。如果不许要发送报文，将uip_len置零即可。
 *
 * The usual way of calling the function is presented by the source
 * code below.
 	通常调用函数的方式可以通过以下代码实现
 \code
  uip_len = devicedriver_poll();
  if(uip_len > 0) {
    uip_input();
    if(uip_len > 0) {
      devicedriver_send();
    }
  }
 \endcode
 *
 * \note If you are writing a uIP device driver that needs ARP
 * (Address Resolution Protocol), e.g., when running uIP over
 * Ethernet, you will need to call the uIP ARP code before calling
 * this function:
 	如果你写了一个 UIP设备驱动需要ARP功能，当UIP协议运行在以太网上时，
	你在调用这些函数之前调用UIP　ARP代码段。
 \code
  #define BUF ((struct uip_eth_hdr *)&uip_buf[0])
  uip_len = ethernet_devicedrver_poll();
  if(uip_len > 0) {
    if(BUF->type == HTONS(UIP_ETHTYPE_IP)) {
      uip_arp_ipin();
      uip_input();
      if(uip_len > 0) {
        uip_arp_out();
	ethernet_devicedriver_send();
      }
    } else if(BUF->type == HTONS(UIP_ETHTYPE_ARP)) {
      uip_arp_arpin();
      if(uip_len > 0) {
	ethernet_devicedriver_send();
      }
    }
 \endcode
 *
 * \hideinitializer
 */
#define uip_input()        uip_process(UIP_DATA)

/**
 * Periodic processing for a connection identified by its number.
 	定期处理以确定连接数。
 *
 * This function does the necessary periodic processing (timers,
 * polling) for a uIP TCP conneciton, and should be called when the
 * periodic uIP timer goes off. It should be called for every
 * connection, regardless of whether they are open of closed.
 	这些函数为TCP连接做必要的定时器处理（定时器、轮询）。
 *
 * When the function returns, it may have an outbound packet waiting
 * for service in the uIP packet buffer, and if so the uip_len
 * variable is set to a value larger than zero. The device driver
 * should be called to send out the packet.
 	当函数返回时，可能会有一个报文等待发送，并且uip_len需要设置大于0。
	设备驱动需要调用函数发送这个报文。
 *
 * The ususal way of calling the function is through a for() loop like
 * this:
 	调用函数的方式通常是通过像for()循环一样
 \code
  for(i = 0; i < UIP_CONNS; ++i) {
    uip_periodic(i);
    if(uip_len > 0) {
      devicedriver_send();
    }
  }
 \endcode
 *
 * \note If you are writing a uIP device driver that needs ARP
 * (Address Resolution Protocol), e.g., when running uIP over
 * Ethernet, you will need to call the uip_arp_out() function before
 * calling the device driver:
 	如果你写了一个设备驱动需要ARP功能，当UIP运行在以太网上，在调用设备驱动之前
	你需要调用uip_arp_out()函数
 \code
  for(i = 0; i < UIP_CONNS; ++i) {
    uip_periodic(i);
    if(uip_len > 0) {
      uip_arp_out();
      ethernet_devicedriver_send();
    }
  }
 \endcode
 *
 * \param conn The number of the connection which is to be periodically polled.
 *	参数conn是需要周期性论查的连接数
 * \hideinitializer
 */
#define uip_periodic(conn) do { uip_conn = &uip_conns[conn]; \
                                uip_process(UIP_TIMER); } while (0)

/**
 *
 *
 */
#define uip_conn_active(conn) (uip_conns[conn].tcpstateflags != UIP_CLOSED)

/**
 * Perform periodic processing for a connection identified by a pointer
 * to its structure.  通过结构体指针用于表示需要定时处理的连接标签
 *
 * Same as uip_periodic() but takes a pointer to the actual uip_conn
 * struct instead of an integer as its argument. This function can be
 * used to force periodic processing of a specific connection.
 * 	与uip_periodoc()相同，但是该宏需要一个具有实际指向uip_conn结构体的指针
 	来替代整形值作为参数。这个函数可用于强制定时处理固定链接

 * \param conn A pointer to the uip_conn struct for the connection to
 * be processed.
 	参数Conn指针指向需要处理的链接
 *
 * \hideinitializer
 */
#define uip_periodic_conn(conn) do { uip_conn = conn; \
                                     uip_process(UIP_TIMER); } while (0)

/**
 * Reuqest that a particular connection should be polled.
 	特定的链接需要轮询？
 *																				 
 * Similar to uip_periodic_conn() but does not perform any timer
 * processing. The application is polled for new data.
 	与uip_periodic_conn()差不多但是不执行任何定时器处理。这个程序是轮询新数据的。
 *
 * \param conn A pointer to the uip_conn struct for the connection to
 * be processed. 参数是需要处理的链接
 *
 * \hideinitializer
 */
#define uip_poll_conn(conn) do { uip_conn = conn; \
                                 uip_process(UIP_POLL_REQUEST); } while (0)


#if UIP_UDP
/**
 * Periodic processing for a UDP connection identified by its number.
 *	需要定期处理的UDP确认连接数

 * This function is essentially the same as uip_periodic(), but for
 * UDP connections. It is called in a similar fashion as the
 * uip_periodic() function:
 	这个程序实质上和uip_periodic()相同，但是用于udp连接。用法和uip_periodic()差不多。
 \code
  for(i = 0; i < UIP_UDP_CONNS; i++) {
    uip_udp_periodic(i);
    if(uip_len > 0) {
      devicedriver_send();
    }
  }
 \endcode
 *
 * \note As for the uip_periodic() function, special care has to be
 * taken when using uIP together with ARP and Ethernet:
 	对于uip_periodic函数，在使用uip ARP时要特别注意。
 \code
  for(i = 0; i < UIP_UDP_CONNS; i++) {
    uip_udp_periodic(i);
    if(uip_len > 0) {
      uip_arp_out();
      ethernet_devicedriver_send();
    }
  }
 \endcode
 *
 * \param conn The number of the UDP connection to be processed.
 *
 * \hideinitializer
 */
#define uip_udp_periodic(conn) do { uip_udp_conn = &uip_udp_conns[conn]; \
                                uip_process(UIP_UDP_TIMER); } while (0)

/**
 * Periodic processing for a UDP connection identified by a pointer to
 * its structure.
	定期处理UDP连接 	
 *
 * Same as uip_udp_periodic() but takes a pointer to the actual
 * uip_conn struct instead of an integer as its argument. This
 * function can be used to force periodic processing of a specific
 * connection.
 	和uip_udp_periodic()相同但是参数必须使用结构体指针代替整形值。
	这个函数可用于强制定期处理固定链接
 *
 * \param conn A pointer to the uip_udp_conn struct for the connection
 * to be processed.
 *
 * \hideinitializer
 */
#define uip_udp_periodic_conn(conn) do { uip_udp_conn = conn; \
                                         uip_process(UIP_UDP_TIMER); } while (0)


#endif /* UIP_UDP */

/**
 * The uIP packet buffer.  uip报文缓冲区
 *
 * The uip_buf array is used to hold incoming and outgoing
 * packets. The device driver should place incoming data into this
 * buffer. When sending data, the device driver should read the link
 * level headers and the TCP/IP headers from this buffer. The size of
 * the link level headers is configured by the UIP_LLH_LEN define.
 	缓冲区用于保存传进来的报文。设备驱动应当将传入数据放入缓冲区。
	当有数据要发送时，设备驱动程序需要从缓冲区读取链路层报文头和TCP/IP报文头。
	链路层报文头的大小通过配置UIP_LLH_LEN定义。
 *
 * \note The application data need not be placed in this buffer, so
 * the device driver must read it from the place pointed to by the
 * uip_appdata pointer as illustrated by the following example:
 	应用数据不需要放到这个缓冲区中，所以设备驱动需要读取应用数据必须从
	uip_appdata 指针指向的地方读起，如下例子：
 \code
 void
 devicedriver_send(void)
 {
    hwsend(&uip_buf[0], UIP_LLH_LEN);
    if(uip_len <= UIP_LLH_LEN + UIP_TCPIP_HLEN) {
      hwsend(&uip_buf[UIP_LLH_LEN], uip_len - UIP_LLH_LEN);
    } else {
      hwsend(&uip_buf[UIP_LLH_LEN], UIP_TCPIP_HLEN);
      hwsend(uip_appdata, uip_len - UIP_TCPIP_HLEN - UIP_LLH_LEN);
    }
 }
 \endcode
 */
extern u8_t uip_buf[UIP_BUFSIZE+2];

/** @} */

/*---------------------------------------------------------------------------*/
/* Functions that are used by the uIP application program. Opening and
 * closing connections, sending and receiving data, etc. is all
 * handled by the functions below.
 	应用程序需要使用这个函数。打开或关闭连接，发送或接收数据等等，都执行以下函数：
*/
/**
 * \defgroup uipappfunc uIP application functions
 * @{
 *
 * Functions used by an application running of top of uIP.
 */

/**
 * Start listening to the specified port.
 *	开始监听固定端口
 * \note Since this function expects the port number in network byte
 * order, a conversion using HTONS() or htons() is necessary.
 *	因为这个函数需要网络字节顺序的端口号，所以转换程序是必要的。
 \code
 uip_listen(HTONS(80));
 \endcode
 *
 * \param port A 16-bit port number in network byte order.
 */
void uip_listen(u16_t port);

/**
 * Stop listening to the specified port.
 	停止监听固定端口
 *
 * \note Since this function expects the port number in network byte
 * order, a conversion using HTONS() or htons() is necessary.
 *
 \code
 uip_unlisten(HTONS(80));
 \endcode
 *
 * \param port A 16-bit port number in network byte order.
 */
void uip_unlisten(u16_t port);

/**
 * Connect to a remote host using TCP.
 	使用TCP链接到远程主机。
 *
 * This function is used to start a new connection to the specified
 * port on the specied host. It allocates a new connection identifier,
 * sets the connection to the SYN_SENT state and sets the
 * retransmission timer to 0. This will cause a TCP SYN segment to be
 * sent out the next time this connection is periodically processed,
 * which usually is done within 0.5 seconds after the call to
 * uip_connect().			  i 
 	这个函数启动一个新连接使用固定端口连接固定主机。函数会分配一个新的连接标签，
	设置该链接为SYN_SENT状态并且设置重传次数为0 这将导致发送完这个TCP_SYN段后，
	下一次这个链接会定时处理，通常是0.5秒内调用一次uip_connect()处理。
 *
 * \note This function is avaliable only if support for active open
 * has been configured by defining UIP_ACTIVE_OPEN to 1 in uipopt.h.
	这个函数只有在UIP_ACTIVVE_OPEN设置为1时才有用。
 *
 * \note Since this function requires the port number to be in network
 * byte order, a conversion using HTONS() or htons() is necessary.
 	需要网络顺序字节，需要转换程序。
 *
 \code
 uip_ipaddr_t ipaddr;

 uip_ipaddr(&ipaddr, 192,168,1,2);
 uip_connect(&ipaddr, HTONS(80));
 \endcode
 *
 * \param ripaddr The IP address of the remote hot.	参数ripaddr是远程主机的IP地址
 *
 * \param port A 16-bit port number in network byte order.
 *
 * \return A pointer to the uIP connection identifier for the new connection,
 * or NULL if no connection could be allocated.
 *
 */
struct uip_conn *uip_connect(uip_ipaddr_t *ripaddr, u16_t port);



/**
 * \internal内部的
 *
 * Check if a connection has outstanding (i.e., unacknowledged) data.
 	
 *
 * \param conn A pointer to the uip_conn structure for the connection.
 *
 * \hideinitializer
 */
 /*len表示连接conn的发送窗口中已经发送但未被确认包的长度*/
#define uip_outstanding(conn) ((conn)->len)

/**
 * Send data on the current connection.	在当前连接发送数据。
 *
 * This function is used to send out a single segment of TCP
 * data. Only applications that have been invoked by uIP for event
 * processing can send data.
 	这个函数用于发送一段TCP数据。仅当应用程序调用事件处理函数才能发送数据。
 *
 * The amount of data that actually is sent out after a call to this
 * funcion is determined by the maximum amount of data TCP allows. uIP
 * will automatically crop the data so that only the appropriate
 * amount of data is sent. The function uip_mss() can be used to query
 * uIP for the amount of data that actually will be sent.
	实际发送的数据量是通过调用这个函数的次数决定的。uip会自动复制数据因此
	要发送适当的数据量。uip_mss()函数可以用来查询实际要发送的数据量。
 *
 * \note This function does not guarantee that the sent data will
 * arrive at the destination. If the data is lost in the network, the
 * application will be invoked with the uip_rexmit() event being
 * set. The application will then have to resend the data using this
 * function.
	这个函数并不能保证发送的数据能到达目的地。如果数据在网络中丢失，
	这个程序会调用uip_rexmit()函数重新发送数据。应用程序会使用这个函数发送这个数据。 	
 *
 * \param data A pointer to the data which is to be sent.
 	参数data指向要发送的数据
 *
 * \param len The maximum amount of data bytes to be sent.
 	参数len是要发送的数据的字节数
 *
 * \hideinitializer
 */
void uip_send(const void *data, int len);

/**
 * The length of any incoming data that is currently avaliable (if avaliable)
 * in the uip_appdata buffer.
 	
 *
 * The test function uip_data() must first be used to check if there
 * is any data available at all.
 * 	测试函数uip_data必须在首次要被使用，用来检查是否有数据。
 * \hideinitializer
 */
/*void uip_datalen(void);*/
#define uip_datalen()       uip_len

/**
 * The length of any out-of-band data (urgent data) that has arrived
 * on the connection.
 *
 * \note The configuration parameter UIP_URGDATA must be set for this
 * function to be enabled.
 *
 * \hideinitializer
 */
#define uip_urgdatalen()    uip_urglen

/**
 * Close the current connection.
 *	关闭当前连接。
 * This function will close the current connection in a nice way.
 *	这个函数会用正确的方式关闭当前连接。
 * \hideinitializer
 */
#define uip_close()         (uip_flags = UIP_CLOSE)

/**
 * Abort the current connection.		
 	中止当前连接
 *
 * This function will abort (reset) the current connection, and is
 * usually used when an error has occured that prevents using the
 * uip_close() function.
 *	这个函数会中止（重置）当前连接，经常用于错误发生的时候防止调用了uip_close()函数。
 * \hideinitializer
 */
#define uip_abort()         (uip_flags = UIP_ABORT)

/**
 * Tell the sending host to stop sending data.
 	告诉发送数据的主机停止发送数据。
 *
 * This function will close our receiver's window so that we stop
 * receiving data for the current connection.
 	这个函数会关闭接收窗口，因此我们会暂停从当前连接里接收数据。
 *
 * \hideinitializer
 */
#define uip_stop()          (uip_conn->tcpstateflags |= UIP_STOPPED)

/**
 * Find out if the current connection has been previously stopped with
 * uip_stop().
 	用于检查当前连接是否停止。
 *
 * \hideinitializer
 */
#define uip_stopped(conn)   ((conn)->tcpstateflags & UIP_STOPPED)

/**
 * Restart the current connection, if is has previously been stopped
 * with uip_stop().
 	重新开启当前连接，如果之前使用uip_stop暂停了连接。
 *
 * This function will open the receiver's window again so that we
 * start receiving data for the current connection.
 	这个函数会再次打开接收串口，因此我们会从当前连接重新接收数据。
 *
 * \hideinitializer
 */
#define uip_restart()         do { uip_flags |= UIP_NEWDATA; \
                                   uip_conn->tcpstateflags &= ~UIP_STOPPED; \
                              } while(0)


/* uIP tests that can be made to determine in what state the current
   connection is, and what the application function should do. 
   	uip测试当前连接的状态，指示应用程序应该做什么*/

/**
 * Is the current connection a UDP connection?
 *	当前连接是UDP连接？
 * This function checks whether the current connection is a UDP connection.
 *	这个函数检查当前连接是否是UDP连接
 * \hideinitializer
 *
 */
#define uip_udpconnection() (uip_conn == NULL)

/**
 * Is new incoming data available?
 	传入一个新的可用数据？
 *
 * Will reduce to non-zero if there is new data for the application
 * present at the uip_appdata pointer. The size of the data is
 * avaliable through the uip_len variable.
 	值非零表示指针指向的新的应用程序的数据存在。数据的大小可以通过uip_len变量获得。	
 * \hideinitializer
 */
#define uip_newdata()   (uip_flags & UIP_NEWDATA)

/**
 * Has previously sent data been acknowledged?
 	上一个发送的数据收到了ACK?
 *
 * Will reduce to non-zero if the previously sent data has been
 * acknowledged by the remote host. This means that the application
 * can send new data.
 	值非零表示远程主机发送了上一个数据的ACK帧，这意味着应用程序可以发送下一个新数据。
 *
 * \hideinitializer
 */
#define uip_acked()   (uip_flags & UIP_ACKDATA)

/**
 * Has the connection just been connected?
 *	连接是否还保持连接？

 * Reduces to non-zero if the current connection has been connected to
 * a remote host. This will happen both if the connection has been
 * actively opened (with uip_connect()) or passively opened (with
 * uip_listen()).
 	值非零表示当前连接仍然保持与远程主机的连接，这回导致连接积极的打开或者被动的打开。 	
 *
 * \hideinitializer
 */
#define uip_connected() (uip_flags & UIP_CONNECTED)

/**
 * Has the connection been closed by the other end?
 *	另一端的连接是否被终端？
 	
 * Is non-zero if the connection has been closed by the remote
 * host. The application may then do the necessary clean-ups.
 *	值非零表示与远程主机的连接被中断。应用程序可能需要做一些必要的清理工作。
 * \hideinitializer
 */
#define uip_closed()    (uip_flags & UIP_CLOSE)

/**
 * Has the connection been aborted by the other end? 
 * 	另一端的连接是否被终端？

 * Non-zero if the current connection has been aborted (reset) by the
 * remote host.
 * 	值非零表示与远程主机的连接被中断（重置）。
 * \hideinitializer
 */
#define uip_aborted()    (uip_flags & UIP_ABORT)

/**
 * Has the connection timed out?
 	连接超时？
 *
 * Non-zero if the current connection has been aborted due to too many
 * retransmissions.
 *	值非零表示当前连接由于太多重传导致连接中断
 * \hideinitializer
 */
#define uip_timedout()    (uip_flags & UIP_TIMEDOUT)

/**
 * Do we need to retransmit previously data?
 	是否需要重传上次发一个数据。
 *
 * Reduces to non-zero if the previously sent data has been lost in
 * the network, and the application should retransmit it. The
 * application should send the exact same data as it did the last
 * time, using the uip_send() function.
 *	值非零表示上一个发送的数据丢失在以太网中，应用程序需要重传它。
 	应用程序要发送相同的数据，使用uip_send()函数。
 * \hideinitializer
 */
#define uip_rexmit()     (uip_flags & UIP_REXMIT)

/**
 * Is the connection being polled by uIP?
 	连接是否需要调查
 *
 * Is non-zero if the reason the application is invoked is that the
 * current connection has been idle for a while and should be
 * polled.		  
 	值非零表示应用程序调查当前连接的原因是因为它闲置了一段时间需要调查（轮询？）
 *
 * The polling event can be used for sending data without having to
 * wait for the remote host to send data.
 	轮询事件可用于发送数据，而不必等待远程主机先发送数据。
 *
 * \hideinitializer
 */
#define uip_poll()       (uip_flags & UIP_POLL)

/**
 * Get the initial maxium segment size (MSS) of the current
 * connection.
 	获得当前连接初始的最大报文段大小
 *
 * \hideinitializer
 */
#define uip_initialmss()             (uip_conn->initialmss)

/**
 * Get the current maxium segment size that can be sent on the current
 * connection.
 	获取当前连接能够发送的最大报文段的大小	
 *
 * The current maxiumum segment size that can be sent on the
 * connection is computed from the receiver's window and the MSS of
 * the connection (which also is available by calling
 * uip_initialmss()).
 	
 *
 * \hideinitializer
 */
#define uip_mss()             (uip_conn->mss)				  

/**
 * Set up a new UDP connection.
 	简历一个新的UDP连接
 *
 * This function sets up a new UDP connection. The function will
 * automatically allocate an unused local port for the new
 * connection. However, another port can be chosen by using the
 * uip_udp_bind() call, after the uip_udp_new() function has been
 * called.
 	该函数用于建立一个新的UDP连接。这个函数会自动的分配一些不适用的本地端口用于新的连接。
	然而，另一个端口被uip_udp_bind()函数使用，之后会调用uip_udp_new()函数。
 *
 * Example:
 \code
 uip_ipaddr_t addr;
 struct uip_udp_conn *c;

 uip_ipaddr(&addr, 192,168,2,1);
 c = uip_udp_new(&addr, HTONS(12345));
 if(c != NULL) {
   uip_udp_bind(c, HTONS(12344));
 }
 \endcode
 * \param ripaddr The IP address of the remote host.
 *
 * \param rport The remote port number in network byte order.
 *
 * \return The uip_udp_conn structure for the new connection or NULL
 * if no connection could be allocated.	 返回一个新的连接的结构体，或者如果没有分配连接，返回空
 */
struct uip_udp_conn *uip_udp_new(uip_ipaddr_t *ripaddr, u16_t rport);

/**
 * Removed a UDP connection.
 	删除一个UDP连接
 *
 * \param conn A pointer to the uip_udp_conn structure for the connection.
 *
 * \hideinitializer
 */
#define uip_udp_remove(conn) (conn)->lport = 0

/**
 * Bind a UDP connection to a local port.
 	绑定一个uDP连接到本地端口
 *
 * \param conn A pointer to the uip_udp_conn structure for the
 * connection.
 	第一个参数指向连UDP连接的结构体的指针
 *
 * \param port The local port number, in network byte order.
 *
 * \hideinitializer
 */
#define uip_udp_bind(conn, port) (conn)->lport = port

/**
 * Send a UDP datagram of length len on the current connection.
 	发送一个len长度的UDP数据包到当前连接
 *
 * This function can only be called in response to a UDP event (poll
 * or newdata). The data must be present in the uip_buf buffer, at the
 * place pointed to by the uip_appdata pointer.
	这个函数仅在响应UDP事件时被调用。要发送的数据报必须存放在uip_buf缓冲区中，
	在uip_appdata指针指向的地方。	
 *
 * \param len The length of the data in the uip_buf buffer.
 	数据报的长度参数在uip_buf缓冲区中
 *
 * \hideinitializer
 */
#define uip_udp_send(len) uip_send((char *)uip_appdata, len)

/** @} */

/* uIP convenience and converting functions. 
	uip方便的转换函数*/

/**
 * \defgroup uipconvfunc uIP conversion functions 转换函数
 * @{
 *
 * These functions can be used for converting between different data
 * formats used by uIP.
 	这些函数可以用与在不同的数据格式之间转换	
 */

/**
 * Construct an IP address from four bytes.构造一个四个字节的IP地址
 *
 * This function constructs an IP address of the type that uIP handles
 * internally from four bytes. The function is handy for specifying IP
 * addresses to use with e.g. the uip_connect() function.
 	这个函数构造一个uIP处理过的四个字节的IP地址，这个函数会使用uip_connect()函数很方便的处理一个固定的IP地址
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr;
 struct uip_conn *c;

 uip_ipaddr(&ipaddr, 192,168,1,2);
 c = uip_connect(&ipaddr, HTONS(80));
 \endcode
 *
 * \param addr A pointer to a uip_ipaddr_t variable that will be
 * filled in with the IP address.
 *
 * \param addr0 The first octet of the IP address.
 * \param addr1 The second octet of the IP address.
 * \param addr2 The third octet of the IP address.
 * \param addr3 The forth octet of the IP address.
 *
 * \hideinitializer
 */
#define uip_ipaddr(addr, addr0,addr1,addr2,addr3) do { \
                     ((u16_t *)(addr))[0] = HTONS(((addr0) << 8) | (addr1)); \
                     ((u16_t *)(addr))[1] = HTONS(((addr2) << 8) | (addr3)); \
                  } while(0)

/**
 * Construct an IPv6 address from eight 16-bit words.
 * 	构造一个ipv6的地址
 * This function constructs an IPv6 address.
 *
 * \hideinitializer
 */
#define uip_ip6addr(addr, addr0,addr1,addr2,addr3,addr4,addr5,addr6,addr7) do { \
                     ((u16_t *)(addr))[0] = HTONS((addr0)); \
                     ((u16_t *)(addr))[1] = HTONS((addr1)); \
                     ((u16_t *)(addr))[2] = HTONS((addr2)); \
                     ((u16_t *)(addr))[3] = HTONS((addr3)); \
                     ((u16_t *)(addr))[4] = HTONS((addr4)); \
                     ((u16_t *)(addr))[5] = HTONS((addr5)); \
                     ((u16_t *)(addr))[6] = HTONS((addr6)); \
                     ((u16_t *)(addr))[7] = HTONS((addr7)); \
                  } while(0)

/**
 * Copy an IP address to another IP address.
 *	拷贝一个IP地址到另一个IP地址里
 * Copies an IP address from one place to another.
 * 	拷贝一个IP地址的副本到另一个地方
 * Example:
 \code
 uip_ipaddr_t ipaddr1, ipaddr2;

 uip_ipaddr(&ipaddr1, 192,16,1,2);
 uip_ipaddr_copy(&ipaddr2, &ipaddr1);
 \endcode
 *
 * \param dest The destination for the copy.用于拷贝功能的目的参数
 * \param src The source from where to copy.用于拷贝功能的源参数
 *
 * \hideinitializer
 */
#if !UIP_CONF_IPV6
#define uip_ipaddr_copy(dest, src) do { \
                     ((u16_t *)dest)[0] = ((u16_t *)src)[0]; \
                     ((u16_t *)dest)[1] = ((u16_t *)src)[1]; \
                  } while(0)
#else /* !UIP_CONF_IPV6 */
#define uip_ipaddr_copy(dest, src) memcpy(dest, src, sizeof(uip_ip6addr_t))
#endif /* !UIP_CONF_IPV6 */

/**
 * Compare two IP addresses
 	比较两个IP地址是否相等
 *
 * Compares two IP addresses.
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr1, ipaddr2;

 uip_ipaddr(&ipaddr1, 192,16,1,2);
 if(uip_ipaddr_cmp(&ipaddr2, &ipaddr1)) {
    printf("They are the same");
 }
 \endcode
 *
 * \param addr1 The first IP address.
 * \param addr2 The second IP address.
 *
 * \hideinitializer
 */
#if !UIP_CONF_IPV6
#define uip_ipaddr_cmp(addr1, addr2) (((u16_t *)addr1)[0] == ((u16_t *)addr2)[0] && \
				      ((u16_t *)addr1)[1] == ((u16_t *)addr2)[1])
#else /* !UIP_CONF_IPV6 */
#define uip_ipaddr_cmp(addr1, addr2) (memcmp(addr1, addr2, sizeof(uip_ip6addr_t)) == 0)
#endif /* !UIP_CONF_IPV6 */

/**
 * Compare two IP addresses with netmasks
 	使用掩码比较两个IP地址
 *
 * Compares two IP addresses with netmasks. The masks are used to mask
 * out the bits that are to be compared.
 	使用掩码比较两个IP地址，这个掩码用来覆盖一些位然后比较，用于确定两个地址是否在同一网段
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr1, ipaddr2, mask;

 uip_ipaddr(&mask, 255,255,255,0);
 uip_ipaddr(&ipaddr1, 192,16,1,2);
 uip_ipaddr(&ipaddr2, 192,16,1,3);
 if(uip_ipaddr_maskcmp(&ipaddr1, &ipaddr2, &mask)) {
    printf("They are the same");
 }
 \endcode
 *
 * \param addr1 The first IP address.
 * \param addr2 The second IP address.
 * \param mask The netmask.
 *
 * \hideinitializer
 */
#define uip_ipaddr_maskcmp(addr1, addr2, mask) \
                          (((((u16_t *)addr1)[0] & ((u16_t *)mask)[0]) == \
                            (((u16_t *)addr2)[0] & ((u16_t *)mask)[0])) && \
                           ((((u16_t *)addr1)[1] & ((u16_t *)mask)[1]) == \
                            (((u16_t *)addr2)[1] & ((u16_t *)mask)[1])))


/**
 * Mask out the network part of an IP address.
	得到一个IP地址的网段
 *
 * Masks out the network part of an IP address, given the address and
 * the netmask.
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr1, ipaddr2, netmask;

 uip_ipaddr(&ipaddr1, 192,16,1,2);
 uip_ipaddr(&netmask, 255,255,255,0);
 uip_ipaddr_mask(&ipaddr2, &ipaddr1, &netmask);
 \endcode
 *
 * In the example above, the variable "ipaddr2" will contain the IP
 * address 192.168.1.0.
 *
 * \param dest Where the result is to be placed.
 * \param src The IP address.
 * \param mask The netmask.
 *
 * \hideinitializer
 */
#define uip_ipaddr_mask(dest, src, mask) do { \
                     ((u16_t *)dest)[0] = ((u16_t *)src)[0] & ((u16_t *)mask)[0]; \
                     ((u16_t *)dest)[1] = ((u16_t *)src)[1] & ((u16_t *)mask)[1]; \
                  } while(0)

/**
 * Pick the first octet of an IP address.
 	选中IP地址的第一个字节
 *
 * Picks out the first octet of an IP address.
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr;
 u8_t octet;

 uip_ipaddr(&ipaddr, 1,2,3,4);
 octet = uip_ipaddr1(&ipaddr);
 \endcode
 *
 * In the example above, the variable "octet" will contain the value 1.
 *
 * \hideinitializer
 */
#define uip_ipaddr1(addr) (htons(((u16_t *)(addr))[0]) >> 8)

/**
 * Pick the second octet of an IP address.
 	选中IP地址的第二个字节
 *
 * Picks out the second octet of an IP address.
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr;
 u8_t octet;

 uip_ipaddr(&ipaddr, 1,2,3,4);
 octet = uip_ipaddr2(&ipaddr);
 \endcode
 *
 * In the example above, the variable "octet" will contain the value 2.
 *
 * \hideinitializer
 */
#define uip_ipaddr2(addr) (htons(((u16_t *)(addr))[0]) & 0xff)

/**
 * Pick the third octet of an IP address.
 	选中IP地址的第三个字节
 *
 * Picks out the third octet of an IP address.
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr;
 u8_t octet;

 uip_ipaddr(&ipaddr, 1,2,3,4);
 octet = uip_ipaddr3(&ipaddr);
 \endcode
 *
 * In the example above, the variable "octet" will contain the value 3.
 *
 * \hideinitializer
 */
#define uip_ipaddr3(addr) (htons(((u16_t *)(addr))[1]) >> 8)

/**
 * Pick the fourth octet of an IP address.
 *							
 	选中IP地址的第四个字节
 * Picks out the fourth octet of an IP address.
 *
 * Example:
 \code
 uip_ipaddr_t ipaddr;
 u8_t octet;

 uip_ipaddr(&ipaddr, 1,2,3,4);
 octet = uip_ipaddr4(&ipaddr);
 \endcode
 *
 * In the example above, the variable "octet" will contain the value 4.
 *
 * \hideinitializer
 */
#define uip_ipaddr4(addr) (htons(((u16_t *)(addr))[1]) & 0xff)

/**
 * Convert 16-bit quantity from host byte order to network byte order.
 	将16位数字从主机字节顺序转换为网络字节顺序
 *
 * This macro is primarily used for converting constants from host
 * byte order to network byte order. For converting variables to
 * network byte order, use the htons() function instead.
 	这个宏主要使用来一个常量从主机字节顺序转换为网络字节顺序。如果要将变量转换为网络字节顺序，
	需要使用htons()函数进行转化。
 *
 * \hideinitializer
 */
#ifndef HTONS
#   if UIP_BYTE_ORDER == UIP_BIG_ENDIAN
#      define HTONS(n) (n)
#   else /* UIP_BYTE_ORDER == UIP_BIG_ENDIAN */
#      define HTONS(n) (u16_t)((((u16_t) (n)) << 8) | (((u16_t) (n)) >> 8))
#   endif /* UIP_BYTE_ORDER == UIP_BIG_ENDIAN */
#else
#error "HTONS already defined!"
#endif /* HTONS */

/**
 * Convert 16-bit quantity from host byte order to network byte order.
	将16位数字从主机字节顺序转换为网络字节顺序
 *
 * This function is primarily used for converting variables from host
 * byte order to network byte order. For converting constants to
 * network byte order, use the HTONS() macro instead.
 	这个宏主要是用来讲一个变量从主机字节顺序转化为网络字节顺序。转换常量需要使用HTONS()宏
 */
#ifndef htons
u16_t htons(u16_t val);
#endif /* htons */
#ifndef ntohs
#define ntohs htons
#endif

/** @} */

/**
 * Pointer to the application data in the packet buffer.
 	指向报文缓冲区中应用程序数据的指针
 *
 * This pointer points to the application data when the application is
 * called. If the application wishes to send data, the application may
 * use this space to write the data into before calling uip_send().
 	当这个函数被调用的时候指针指向应用程序的数据报文。如果这个程序想要发送数据，
	在调用uip_send()发送数据之前，需要指向的空间写报文才行。
 */
extern void *uip_appdata;

#if UIP_URGDATA > 0
/* u8_t *uip_urgdata:
 *
 * This pointer points to any urgent data that has been received. Only
 * present if compiled with support for urgent data (UIP_URGDATA).
 	这个指针指向任何接收到的urgent数据报文。只有选择编译了urgent data这项功能，这个指针才存在。
 */
extern void *uip_urgdata;
#endif /* UIP_URGDATA > 0 */


/**
 * \defgroup uipdrivervars Variables used in uIP device drivers
	uip中uipdriervars变量被用于设备驱动 	
 * @{
 *
 * uIP has a few global variables that are used in device drivers for
 * uIP.
 	在uip协议中只提供和很少的的全局变量给设备驱动使用
 */

/**
 * The length of the packet in the uip_buf buffer.
 	uip_buf缓冲区中报文的长度
 *
 * The global variable uip_len holds the length of the packet in the
 * uip_buf buffer.			 
 	这个全局变量uip_len保存了报文缓冲区中报文的长度
 *
 * When the network device driver calls the uIP input function,
 * uip_len should be set to the length of the packet in the uip_buf
 * buffer.
 	当网络设备驱动程序被调用，该变量应当被设置为报文缓冲区中报文的长度值
 *
 * When sending packets, the device driver should use the contents of
 * the uip_len variable to determine the length of the outgoing
 * packet.
 	当需要发送报文时，设备驱动程序需要给变量uip_len赋值，已决定应当发送的报文段的长度是多少。
 *
 */
extern u16_t uip_len;

/** @} */

#if UIP_URGDATA > 0
extern u16_t uip_urglen, uip_surglen;
#endif /* UIP_URGDATA > 0 */


/**
 * Representation of a uIP TCP connection.
 	表示一个TCP连接
 *
 * The uip_conn structure is used for identifying a connection. All
 * but one field in the structure are to be considered read-only by an
 * application. The only exception is the appstate field whos purpose
 * is to let the application store application-specific state (e.g.,
 * file pointers) for the connection. The type of this field is
 * configured in the "uipopt.h" header file.
 */
struct uip_conn {
  uip_ipaddr_t ripaddr;   /**< The IP address of the remote host. 远程主机的地址*/

  u16_t lport;        /**< The local TCP port, in network byte order. 本地主机的TCP端口号，使用网络字节顺序*/
  u16_t rport;        /**< The local remote TCP port, in network byte
			 order. 远程主机的TCP端口号，使用网络字节顺序*/
/* 接收窗口中可以接收的下一字节序号*/
  u8_t rcv_nxt[4];    /**< The sequence number that we expect to
			 receive next. 期待接收的下一个字节的序号*/
/* 发送窗口中下一个要发送字节的序号*/			 	
  u8_t snd_nxt[4];    /**< The sequence number that was last sent by
                         us. */
/*发送窗口中已经发送但未被确认包的长度*/						 	
  u16_t len;          /**< Length of the data that was previously sent. 前一个被发送的报文的长度*/
  u16_t mss;          /**< Current maximum segment size for the
			 connection. 当前连接能发送的最大报文段的大小*/
  u16_t initialmss;   /**< Initial maximum segment size for the
			 connection. 初始的最大报文段大小*/
  u8_t sa;            /**< Retransmission time-out calculation state
			 variable. 计算需要重传超时的时间*/
  u8_t sv;            /**< Retransmission time-out calculation state
			 variable. */
/*重发超时值*/			 	
  u8_t rto;           /**< Retransmission time-out. 重发超时值*/
  u8_t tcpstateflags; /**< TCP state and flags. 状态标识*/
/* 每次perodic timer超时时timer-- ,见uip_proecess() */  
  u8_t timer;         /**< The retransmission timer. */
  /* 上一个包的重发次数*/
  u8_t nrtx;          /**< The number of retransmissions for the last
			 segment sent. 上一个报文段重传的次数*/

  /** The application state. 用户程序状态标识*/
  uip_tcp_appstate_t appstate;
};


/**
 * Pointer to the current TCP connection.	当前TCP连接的指针
 *
 * The uip_conn pointer can be used to access the current TCP
 * connection.
 	这个指针可以用来访问当前TCP连接
 */
extern struct uip_conn *uip_conn;
/* The array containing all uIP connections. 
	这个数组包含了所有的UIP协议栈的连接，默认设置为最大连接数40*/
extern struct uip_conn uip_conns[UIP_CONNS];
/**
 * \addtogroup uiparch
 * @{
 */

/**
 * 4-byte array used for the 32-bit sequence number calculations.
 	4个字节的数组用来计算32位序列号
 */
extern u8_t uip_acc32[4];

/** @} */


#if UIP_UDP
/**
 * Representation of a uIP UDP connection.
 	表示UDP连接启用
 */
struct uip_udp_conn {
  uip_ipaddr_t ripaddr;   /**< The IP address of the remote peer. 远程对等的IP地址*/
  u16_t lport;        /**< The local port number in network byte order. 本地端口号，使用网络字节顺序*/
  u16_t rport;        /**< The remote port number in network byte order. 远程主机端口号，使用网络字节顺序*/
  u8_t  ttl;          /**< Default time-to-live. 默认生存时间*/

  /** The application state. 应用程序状态标签*/
  uip_udp_appstate_t appstate;
};

/**
 * The current UDP connection. 当前连接
 */
extern struct uip_udp_conn *uip_udp_conn;
extern struct uip_udp_conn uip_udp_conns[UIP_UDP_CONNS];
#endif /* UIP_UDP */

/**
 * The structure holding the TCP/IP statistics that are gathered if
 * UIP_STATISTICS is set to 1.
 	当UIP_STATISTICS被设置为1，分析统计用
 *
 */
struct uip_stats {
  struct {
    uip_stats_t recv;     /**< Number of received packets at the IP
			     layer. IP层接收到的包的数量*/
    uip_stats_t sent;     /**< Number of sent packets at the IP
			     layer. IP层发送的包的数量*/
    uip_stats_t drop;     /**< Number of dropped packets at the IP
			     layer. IP层丢弃的包的数量*/
    uip_stats_t vhlerr;   /**< Number of packets dropped due to wrong
			     IP version or header length. */
    uip_stats_t hblenerr; /**< Number of packets dropped due to wrong
			     IP length, high byte. */
    uip_stats_t lblenerr; /**< Number of packets dropped due to wrong
			     IP length, low byte. */
    uip_stats_t fragerr;  /**< Number of packets dropped since they
			     were IP fragments. */
    uip_stats_t chkerr;   /**< Number of packets dropped due to IP
			     checksum errors. */
    uip_stats_t protoerr; /**< Number of packets dropped since they
			     were neither ICMP, UDP nor TCP. */
  } ip;                   /**< IP statistics. */
  struct {
    uip_stats_t recv;     /**< Number of received ICMP packets. */
    uip_stats_t sent;     /**< Number of sent ICMP packets. */
    uip_stats_t drop;     /**< Number of dropped ICMP packets. */
    uip_stats_t typeerr;  /**< Number of ICMP packets with a wrong
			     type. */
  } icmp;                 /**< ICMP statistics. */
  struct {
    uip_stats_t recv;     /**< Number of recived TCP segments. */
    uip_stats_t sent;     /**< Number of sent TCP segments. */
    uip_stats_t drop;     /**< Number of dropped TCP segments. */
    uip_stats_t chkerr;   /**< Number of TCP segments with a bad
			     checksum. */
    uip_stats_t ackerr;   /**< Number of TCP segments with a bad ACK
			     number. */
    uip_stats_t rst;      /**< Number of recevied TCP RST (reset) segments. */
    uip_stats_t rexmit;   /**< Number of retransmitted TCP segments. */
    uip_stats_t syndrop;  /**< Number of dropped SYNs due to too few
			     connections was avaliable. */
    uip_stats_t synrst;   /**< Number of SYNs for closed ports,
			     triggering a RST. */
  } tcp;                  /**< TCP statistics. */
#if UIP_UDP
  struct {
    uip_stats_t recv;     /**< Number of recived UDP segments. */
    uip_stats_t sent;     /**< Number of sent UDP segments. */
    uip_stats_t drop;     /**< Number of dropped UDP segments. */
    uip_stats_t chkerr;   /**< Number of UDP segments with a bad
			     checksum. */
  } udp;                  /**< UDP statistics. */
#endif /* UIP_UDP */
};

/**
 * The uIP TCP/IP statistics. TCP/IIP统计
 *
 * This is the variable in which the uIP TCP/IP statistics are gathered.这个变量是用于TCP/IP统计信息用
 */
extern struct uip_stats uip_stat;


/*---------------------------------------------------------------------------*/
/* All the stuff below this point is internal to uIP and should not be
 * used directly by an application or by a device driver.以下的所有的东西都不应该由应用程序或设备驱动直接调用
 */
/*---------------------------------------------------------------------------*/
/* u8_t uip_flags:
 *
 * When the application is called, uip_flags will contain the flags
 * that are defined in this file. Please read below for more
 * infomation.
 	当应用程序被调用是，uip_flags定义在这个文件，请阅读以下更多信息
 */
extern u8_t uip_flags;

/* The following flags may be set in the global variable uip_flags
   before calling the application callback. The UIP_ACKDATA,
   UIP_NEWDATA, and UIP_CLOSE flags may both be set at the same time,
   whereas the others are mutualy exclusive. Note that these flags
   should *NOT* be accessed directly, but only through the uIP
   functions/macros. 
   	下面的标识uip_flags可能被设置为全局变量，在调用应用程序之前返回。
	UIP_ACKDATA,UIP_NEWDATA,UIP_CLOSE标识可能会同时被设置，可能会被xx排斥。
	需要注意的是这些标识不应该被直接访问，只能通过UIP协议栈函数或宏访问。*/

/*发送窗口中未被确认的数据已经得到确认, 可以发送新数据而不是重发*/
#define UIP_ACKDATA   1     /* Signifies that the outstanding data was
			       acked and the application should send
			       out new data instead of retransmitting
			       the last data. */
/* 接收到的包里含有用户数据*/			       
#define UIP_NEWDATA   2     /* Flags the fact that the peer has sent
			       us new data. */
#define UIP_REXMIT    4     /* Tells the application to retransmit the
			       data that was last sent. 告诉应用程序重传上一个报文*/
#define UIP_POLL      8     /* Used for polling the application, to
			       check if the application has data that
			       it wants to send. 用于轮询用户程序，检查应用程序是否需要发送报文*/
#define UIP_CLOSE     16    /* The remote host has closed the
			       connection, thus the connection has
			       gone away. Or the application signals
			       that it wants to close the
			       connection. 远程主机关闭了连接，因此连接需要被丢弃。或用户程序使用这个信号，想关闭这个连接*/
#define UIP_ABORT     32    /* The remote host has aborted the
			       connection, thus the connection has
			       gone away. Or the application signals
			       that it wants to abort the
			       connection. 远程主机中断了连接，因此连接丢弃，或者用户程序想要终端连接*/
/*一个连接已经建立起来了(进入了ESTABLISHED状态)*/			      
#define UIP_CONNECTED 64    /* We have got a connection from a remote
                               host and have set up a new connection
                               for it, or an active connection has
                               been successfully established. 
							   	查询一个链接是否被建立或是否活跃*/

#define UIP_TIMEDOUT  128   /* The connection has been aborted due to
			       too many retransmissions. 连接是否由于重传超时而终端*/

/* uip_process(flag):
 *
 * The actual uIP function which does all the work.
 	网卡收到数据是，该程序会遍历uip_udp_conns数组，如果包的目的端口
	与本机端口不匹配，或者远程端口与uip_udp_new中的端口不匹配，uip会
	直接丢弃这个包。
 */
void uip_process(u8_t flag);

/* The following flags are passed as an argument to the uip_process()
   function. They are used to distinguish between the two cases where
   uip_process() is called. It can be called either because we have
   incoming data that should be processed, or because the periodic
   timer has fired. These values are never used directly, but only in
   the macrose defined in this file. 
   	*/

#define UIP_DATA          1     /* Tells uIP that there is incoming
				   data in the uip_buf buffer. The
				   length of the data is stored in the
				   global variable uip_len. 告诉UIP传入了一个包*/
#define UIP_TIMER         2     /* Tells uIP that the periodic timer
				   has fired. 告诉UP周期定时器失效*/
#define UIP_POLL_REQUEST  3     /* Tells uIP that a connection should
				   be polled. 告诉UIP连接需要被检查*/
#define UIP_UDP_SEND_CONN 4     /* Tells uIP that a UDP datagram
				   should be constructed in the
				   uip_buf buffer. 告诉UIP需要创建一个UDP数据帧放在缓冲区中*/
#if UIP_UDP
#define UIP_UDP_TIMER     5
#endif /* UIP_UDP */

/* The TCP states used in the uip_conn->tcpstateflags. */
#define UIP_CLOSED      0
#define UIP_SYN_RCVD    1
#define UIP_SYN_SENT    2
#define UIP_ESTABLISHED 3
#define UIP_FIN_WAIT_1  4
#define UIP_FIN_WAIT_2  5
#define UIP_CLOSING     6
#define UIP_TIME_WAIT   7
#define UIP_LAST_ACK    8
#define UIP_TS_MASK     15

#define UIP_STOPPED      16

/* The TCP and IP headers. TCP协议的IP报文头*/
struct uip_tcpip_hdr {
#if UIP_CONF_IPV6
  /* IPv6 header. */
  u8_t vtc,
    tcflow;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
#else /* UIP_CONF_IPV6 */
  /* IPv4 header. */
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
#endif /* UIP_CONF_IPV6 */

  /* TCP header. */
  u16_t srcport,
    destport;
  u8_t seqno[4],
    ackno[4],
    tcpoffset,	/*前4位是TCP首部长度*/
    flags,		/*后6位是TCP包标志位*/
    wnd[2];
  u16_t tcpchksum;
  u8_t urgp[2];
  u8_t optdata[4];
};

/* The ICMP and IP headers. ICMP协议的IP报文的头*/
struct uip_icmpip_hdr {
#if UIP_CONF_IPV6
  /* IPv6 header. */
  u8_t vtc,
    tcf;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
#else /* UIP_CONF_IPV6 */
  /* IPv4 header. */
  u8_t vhl,
    tos,
    len[2],		/*16位的IP包总长度, 包括IP头+TCP包, 不含FCS*/
    ipid[2],	/* 16位的IP包标识*/
    ipoffset[2],
    ttl,
    proto;
  u16_t ipchksum;
  u16_t srcipaddr[2],
    destipaddr[2];
#endif /* UIP_CONF_IPV6 */

  /* ICMP (echo) header. */
  u8_t type, icode;
  u16_t icmpchksum;
#if !UIP_CONF_IPV6
  u16_t id, seqno;
#else /* !UIP_CONF_IPV6 */
  u8_t flags, reserved1, reserved2, reserved3;
  u8_t icmp6data[16];
  u8_t options[1];
#endif /* !UIP_CONF_IPV6 */
};


/* The UDP and IP headers. */
struct uip_udpip_hdr {
#if UIP_CONF_IPV6
  /* IPv6 header. */
  u8_t vtc,
    tcf;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
#else /* UIP_CONF_IPV6 */
  /* IP header. */
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
#endif /* UIP_CONF_IPV6 */

  /* UDP header. */
  u16_t srcport,
    destport;
  u16_t udplen;
  u16_t udpchksum;
};



/**
 * The buffer size available for user data in the \ref uip_buf buffer.
 *	这个缓冲区大小变量用于在用户包的缓冲区中

 * This macro holds the available size for user data in the \ref
 * uip_buf buffer. The macro is intended to be used for checking
 * bounds of available user data.
 	这个宏保存了用户包缓冲区的大小配置。目的是检查约束用户报文
 *
 * Example:
 \code
 snprintf(uip_appdata, UIP_APPDATA_SIZE, "%u\n", i);
 \endcode
 *
 * \hideinitializer
 */
#define UIP_APPDATA_SIZE (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)


#define UIP_PROTO_ICMP  1
#define UIP_PROTO_TCP   6
#define UIP_PROTO_UDP   17
#define UIP_PROTO_ICMP6 58

/* Header sizes. */
#if UIP_CONF_IPV6
#define UIP_IPH_LEN    40
#else /* UIP_CONF_IPV6 */
#define UIP_IPH_LEN    20    /* Size of IP header IP报文头的大小*/
#endif /* UIP_CONF_IPV6 */
#define UIP_UDPH_LEN    8    /* Size of UDP header UDP报文头的大小*/
#define UIP_TCPH_LEN   20    /* Size of TCP header TCP报文头的大小*/
#define UIP_IPUDPH_LEN (UIP_UDPH_LEN + UIP_IPH_LEN)    /* Size of IP +
							  UDP
							  header */
#define UIP_IPTCPH_LEN (UIP_TCPH_LEN + UIP_IPH_LEN)    /* Size of IP +
							  TCP
							  header */
#define UIP_TCPIP_HLEN UIP_IPTCPH_LEN


#if UIP_FIXEDADDR
extern const uip_ipaddr_t uip_hostaddr, uip_netmask, uip_draddr;
#else /* UIP_FIXEDADDR */
extern uip_ipaddr_t uip_hostaddr, uip_netmask, uip_draddr;
#endif /* UIP_FIXEDADDR */



/**
 * Representation of a 48-bit Ethernet address.
 */
struct uip_eth_addr {
  u8_t addr[6];
};

/**
 * Calculate the Internet checksum over a buffer.计算因特网校验和
 *
 * The Internet checksum is the one's complement of the one's
 * complement sum of all 16-bit words in the buffer.
 	英特网校验和是补充
 *
 * See RFC1071.
 *
 * \param buf A pointer to the buffer over which the checksum is to be
 * computed.  需要计算校验和的buffer
 *
 * \param len The length of the buffer over which the checksum is to
 * be computed.			
 *
 * \return The Internet checksum of the buffer.
 */
u16_t uip_chksum(u16_t *buf, u16_t len);

/**
 * Calculate the IP header checksum of the packet header in uip_buf.
 *
 * The IP header checksum is the Internet checksum of the 20 bytes of
 * the IP header.
 *
 * \return The IP header checksum of the IP header in the uip_buf
 * buffer.
 */
u16_t uip_ipchksum(void);

/**
 * Calculate the TCP checksum of the packet in uip_buf and uip_appdata.
 *
 * The TCP checksum is the Internet checksum of data contents of the
 * TCP segment, and a pseudo-header as defined in RFC793.
 *
 * \return The TCP checksum of the TCP segment in uip_buf and pointed
 * to by uip_appdata.
 */
u16_t uip_tcpchksum(void);

/**
 * Calculate the UDP checksum of the packet in uip_buf and uip_appdata.
 *
 * The UDP checksum is the Internet checksum of data contents of the
 * UDP segment, and a pseudo-header as defined in RFC768.
 *
 * \return The UDP checksum of the UDP segment in uip_buf and pointed
 * to by uip_appdata.
 */
u16_t uip_udpchksum(void);


#endif /* __UIP_H__ */


/** @} */
