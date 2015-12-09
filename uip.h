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
 * Repressentation of an IP address.  ��ʾһ��IP��ַ
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
 	���ȣ���ϵͳ�е��������������ʼ�������ڶ�ʱ���ʹ�����������������������
 */

/**
 * \defgroup uipconffunc uIP configuration functions
 * @{
 *
 * The uIP configuration functions are used for setting run-time
 * parameters in uIP such as IP addresses.
 	uip���ú��������ڳ�������ʱ����uip��������������IP��ַ
 */

/**
 * Set the IP address of this host.	�������������IP��ַ
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
 * Get the IP address of this host. �õ���������IP��ַ
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
 * Set the default router's IP address.	 ����Ĭ��·������IP��ַ
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
 * Set the netmask.	��������
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
 * Get the default router's IP address.	�õ�Ĭ��·������IP��ַ
 *
 * \param addr A pointer to a uip_ipaddr_t variable that will be
 * filled in with the IP address of the default router.
 *
 * \hideinitializer
 */
#define uip_getdraddr(addr) uip_ipaddr_copy((addr), uip_draddr)

/**
 * Get the netmask.	�ĵ�����
 *
 * \param addr A pointer to a uip_ipaddr_t variable that will be
 * filled in with the value of the netmask.
 *
 * \hideinitializer
 */
#define uip_getnetmask(addr) uip_ipaddr_copy((addr), uip_netmask)

/** @} */

/**
 * \defgroup uipinit uIP initialization functions uip��ʼ������
 * @{
 *
 * The uIP initialization functions are used for booting uIP.
	�����ʼ��������������UIPЭ��ջ
 */

/**
 * uIP initialization function.	UIP��ʼ������
 *
 * This function should be called at boot up to initilize the uIP
 * TCP/IP stack.
 	�����������ʱ�򱻵���������ʼ��TCP/IPЭ��ջ
 */
void uip_init(void);

/**
 * uIP initialization function.
 *
 * This function may be used at boot time to set the initial ip_id.
 	�����������������ʱ���ó�ʼip_id
 */
void uip_setipid(u16_t id);

/** @} */

/**
 * \defgroup uipdevfunc uIP device driver functions	UIP�豸��������
 * @{
 *
 * These functions are used by a network device driver for interacting
 * with uIP.
 	�������������ʹ�����豸������UIP���н�����
 */

/**
 * Process an incoming packet. ����һ������ı���
 *
 * This function should be called when the device driver has received
 * a packet from the network. The packet from the device driver must
 * be present in the uip_buf buffer, and the length of the packet
 * should be placed in the uip_len variable.
 	���豸�����������Ͻ��յ�һ�����ĺ������������������յ��ı��ı������uip_buf�������У�
	���ĳ�����Ҫ����uip_len������
 *
 * When the function returns, there may be an outbound packet placed
 * in the uip_buf packet buffer. If so, the uip_len variable is set to
 * the length of the packet. If no packet is to be sent out, the
 * uip_len variable is set to 0.
 	����������ʱ��������Ҫ���͵ı��Ļ�����uip_buf�������У����uip_len����Ҳ��Ҫ
	�޸ĳɷ��ͱ��ĵĳ��ȡ��������Ҫ���ͱ��ģ���uip_len���㼴�ɡ�
 *
 * The usual way of calling the function is presented by the source
 * code below.
 	ͨ�����ú����ķ�ʽ����ͨ�����´���ʵ��
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
 	�����д��һ�� UIP�豸������ҪARP���ܣ���UIPЭ����������̫����ʱ��
	���ڵ�����Щ����֮ǰ����UIP��ARP����Ρ�
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
 	���ڴ�����ȷ����������
 *
 * This function does the necessary periodic processing (timers,
 * polling) for a uIP TCP conneciton, and should be called when the
 * periodic uIP timer goes off. It should be called for every
 * connection, regardless of whether they are open of closed.
 	��Щ����ΪTCP��������Ҫ�Ķ�ʱ��������ʱ������ѯ����
 *
 * When the function returns, it may have an outbound packet waiting
 * for service in the uIP packet buffer, and if so the uip_len
 * variable is set to a value larger than zero. The device driver
 * should be called to send out the packet.
 	����������ʱ�����ܻ���һ�����ĵȴ����ͣ�����uip_len��Ҫ���ô���0��
	�豸������Ҫ���ú�������������ġ�
 *
 * The ususal way of calling the function is through a for() loop like
 * this:
 	���ú����ķ�ʽͨ����ͨ����for()ѭ��һ��
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
 	�����д��һ���豸������ҪARP���ܣ���UIP��������̫���ϣ��ڵ����豸����֮ǰ
	����Ҫ����uip_arp_out()����
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
 *	����conn����Ҫ�������۲��������
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
 * to its structure.  ͨ���ṹ��ָ�����ڱ�ʾ��Ҫ��ʱ��������ӱ�ǩ
 *
 * Same as uip_periodic() but takes a pointer to the actual uip_conn
 * struct instead of an integer as its argument. This function can be
 * used to force periodic processing of a specific connection.
 * 	��uip_periodoc()��ͬ�����Ǹú���Ҫһ������ʵ��ָ��uip_conn�ṹ���ָ��
 	���������ֵ��Ϊ�������������������ǿ�ƶ�ʱ����̶�����

 * \param conn A pointer to the uip_conn struct for the connection to
 * be processed.
 	����Connָ��ָ����Ҫ���������
 *
 * \hideinitializer
 */
#define uip_periodic_conn(conn) do { uip_conn = conn; \
                                     uip_process(UIP_TIMER); } while (0)

/**
 * Reuqest that a particular connection should be polled.
 	�ض���������Ҫ��ѯ��
 *																				 
 * Similar to uip_periodic_conn() but does not perform any timer
 * processing. The application is polled for new data.
 	��uip_periodic_conn()��൫�ǲ�ִ���κζ�ʱ�����������������ѯ�����ݵġ�
 *
 * \param conn A pointer to the uip_conn struct for the connection to
 * be processed. ��������Ҫ���������
 *
 * \hideinitializer
 */
#define uip_poll_conn(conn) do { uip_conn = conn; \
                                 uip_process(UIP_POLL_REQUEST); } while (0)


#if UIP_UDP
/**
 * Periodic processing for a UDP connection identified by its number.
 *	��Ҫ���ڴ����UDPȷ��������

 * This function is essentially the same as uip_periodic(), but for
 * UDP connections. It is called in a similar fashion as the
 * uip_periodic() function:
 	�������ʵ���Ϻ�uip_periodic()��ͬ����������udp���ӡ��÷���uip_periodic()��ࡣ
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
 	����uip_periodic��������ʹ��uip ARPʱҪ�ر�ע�⡣
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
	���ڴ���UDP���� 	
 *
 * Same as uip_udp_periodic() but takes a pointer to the actual
 * uip_conn struct instead of an integer as its argument. This
 * function can be used to force periodic processing of a specific
 * connection.
 	��uip_udp_periodic()��ͬ���ǲ�������ʹ�ýṹ��ָ���������ֵ��
	�������������ǿ�ƶ��ڴ���̶�����
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
 * The uIP packet buffer.  uip���Ļ�����
 *
 * The uip_buf array is used to hold incoming and outgoing
 * packets. The device driver should place incoming data into this
 * buffer. When sending data, the device driver should read the link
 * level headers and the TCP/IP headers from this buffer. The size of
 * the link level headers is configured by the UIP_LLH_LEN define.
 	���������ڱ��洫�����ı��ġ��豸����Ӧ�����������ݷ��뻺������
	��������Ҫ����ʱ���豸����������Ҫ�ӻ�������ȡ��·�㱨��ͷ��TCP/IP����ͷ��
	��·�㱨��ͷ�Ĵ�Сͨ������UIP_LLH_LEN���塣
 *
 * \note The application data need not be placed in this buffer, so
 * the device driver must read it from the place pointed to by the
 * uip_appdata pointer as illustrated by the following example:
 	Ӧ�����ݲ���Ҫ�ŵ�����������У������豸������Ҫ��ȡӦ�����ݱ����
	uip_appdata ָ��ָ��ĵط������������ӣ�
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
 	Ӧ�ó�����Ҫʹ������������򿪻�ر����ӣ����ͻ�������ݵȵȣ���ִ�����º�����
*/
/**
 * \defgroup uipappfunc uIP application functions
 * @{
 *
 * Functions used by an application running of top of uIP.
 */

/**
 * Start listening to the specified port.
 *	��ʼ�����̶��˿�
 * \note Since this function expects the port number in network byte
 * order, a conversion using HTONS() or htons() is necessary.
 *	��Ϊ���������Ҫ�����ֽ�˳��Ķ˿ںţ�����ת�������Ǳ�Ҫ�ġ�
 \code
 uip_listen(HTONS(80));
 \endcode
 *
 * \param port A 16-bit port number in network byte order.
 */
void uip_listen(u16_t port);

/**
 * Stop listening to the specified port.
 	ֹͣ�����̶��˿�
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
 	ʹ��TCP���ӵ�Զ��������
 *
 * This function is used to start a new connection to the specified
 * port on the specied host. It allocates a new connection identifier,
 * sets the connection to the SYN_SENT state and sets the
 * retransmission timer to 0. This will cause a TCP SYN segment to be
 * sent out the next time this connection is periodically processed,
 * which usually is done within 0.5 seconds after the call to
 * uip_connect().			  i 
 	�����������һ��������ʹ�ù̶��˿����ӹ̶����������������һ���µ����ӱ�ǩ��
	���ø�����ΪSYN_SENT״̬���������ش�����Ϊ0 �⽫���·��������TCP_SYN�κ�
	��һ��������ӻᶨʱ����ͨ����0.5���ڵ���һ��uip_connect()����
 *
 * \note This function is avaliable only if support for active open
 * has been configured by defining UIP_ACTIVE_OPEN to 1 in uipopt.h.
	�������ֻ����UIP_ACTIVVE_OPEN����Ϊ1ʱ�����á�
 *
 * \note Since this function requires the port number to be in network
 * byte order, a conversion using HTONS() or htons() is necessary.
 	��Ҫ����˳���ֽڣ���Ҫת������
 *
 \code
 uip_ipaddr_t ipaddr;

 uip_ipaddr(&ipaddr, 192,168,1,2);
 uip_connect(&ipaddr, HTONS(80));
 \endcode
 *
 * \param ripaddr The IP address of the remote hot.	����ripaddr��Զ��������IP��ַ
 *
 * \param port A 16-bit port number in network byte order.
 *
 * \return A pointer to the uIP connection identifier for the new connection,
 * or NULL if no connection could be allocated.
 *
 */
struct uip_conn *uip_connect(uip_ipaddr_t *ripaddr, u16_t port);



/**
 * \internal�ڲ���
 *
 * Check if a connection has outstanding (i.e., unacknowledged) data.
 	
 *
 * \param conn A pointer to the uip_conn structure for the connection.
 *
 * \hideinitializer
 */
 /*len��ʾ����conn�ķ��ʹ������Ѿ����͵�δ��ȷ�ϰ��ĳ���*/
#define uip_outstanding(conn) ((conn)->len)

/**
 * Send data on the current connection.	�ڵ�ǰ���ӷ������ݡ�
 *
 * This function is used to send out a single segment of TCP
 * data. Only applications that have been invoked by uIP for event
 * processing can send data.
 	����������ڷ���һ��TCP���ݡ�����Ӧ�ó�������¼����������ܷ������ݡ�
 *
 * The amount of data that actually is sent out after a call to this
 * funcion is determined by the maximum amount of data TCP allows. uIP
 * will automatically crop the data so that only the appropriate
 * amount of data is sent. The function uip_mss() can be used to query
 * uIP for the amount of data that actually will be sent.
	ʵ�ʷ��͵���������ͨ��������������Ĵ��������ġ�uip���Զ������������
	Ҫ�����ʵ�����������uip_mss()��������������ѯʵ��Ҫ���͵���������
 *
 * \note This function does not guarantee that the sent data will
 * arrive at the destination. If the data is lost in the network, the
 * application will be invoked with the uip_rexmit() event being
 * set. The application will then have to resend the data using this
 * function.
	������������ܱ�֤���͵������ܵ���Ŀ�ĵء���������������ж�ʧ��
	�����������uip_rexmit()�������·������ݡ�Ӧ�ó����ʹ�������������������ݡ� 	
 *
 * \param data A pointer to the data which is to be sent.
 	����dataָ��Ҫ���͵�����
 *
 * \param len The maximum amount of data bytes to be sent.
 	����len��Ҫ���͵����ݵ��ֽ���
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
 * 	���Ժ���uip_data�������״�Ҫ��ʹ�ã���������Ƿ������ݡ�
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
 *	�رյ�ǰ���ӡ�
 * This function will close the current connection in a nice way.
 *	�������������ȷ�ķ�ʽ�رյ�ǰ���ӡ�
 * \hideinitializer
 */
#define uip_close()         (uip_flags = UIP_CLOSE)

/**
 * Abort the current connection.		
 	��ֹ��ǰ����
 *
 * This function will abort (reset) the current connection, and is
 * usually used when an error has occured that prevents using the
 * uip_close() function.
 *	�����������ֹ�����ã���ǰ���ӣ��������ڴ�������ʱ���ֹ������uip_close()������
 * \hideinitializer
 */
#define uip_abort()         (uip_flags = UIP_ABORT)

/**
 * Tell the sending host to stop sending data.
 	���߷������ݵ�����ֹͣ�������ݡ�
 *
 * This function will close our receiver's window so that we stop
 * receiving data for the current connection.
 	���������رս��մ��ڣ�������ǻ���ͣ�ӵ�ǰ������������ݡ�
 *
 * \hideinitializer
 */
#define uip_stop()          (uip_conn->tcpstateflags |= UIP_STOPPED)

/**
 * Find out if the current connection has been previously stopped with
 * uip_stop().
 	���ڼ�鵱ǰ�����Ƿ�ֹͣ��
 *
 * \hideinitializer
 */
#define uip_stopped(conn)   ((conn)->tcpstateflags & UIP_STOPPED)

/**
 * Restart the current connection, if is has previously been stopped
 * with uip_stop().
 	���¿�����ǰ���ӣ����֮ǰʹ��uip_stop��ͣ�����ӡ�
 *
 * This function will open the receiver's window again so that we
 * start receiving data for the current connection.
 	����������ٴδ򿪽��մ��ڣ�������ǻ�ӵ�ǰ�������½������ݡ�
 *
 * \hideinitializer
 */
#define uip_restart()         do { uip_flags |= UIP_NEWDATA; \
                                   uip_conn->tcpstateflags &= ~UIP_STOPPED; \
                              } while(0)


/* uIP tests that can be made to determine in what state the current
   connection is, and what the application function should do. 
   	uip���Ե�ǰ���ӵ�״̬��ָʾӦ�ó���Ӧ����ʲô*/

/**
 * Is the current connection a UDP connection?
 *	��ǰ������UDP���ӣ�
 * This function checks whether the current connection is a UDP connection.
 *	���������鵱ǰ�����Ƿ���UDP����
 * \hideinitializer
 *
 */
#define uip_udpconnection() (uip_conn == NULL)

/**
 * Is new incoming data available?
 	����һ���µĿ������ݣ�
 *
 * Will reduce to non-zero if there is new data for the application
 * present at the uip_appdata pointer. The size of the data is
 * avaliable through the uip_len variable.
 	ֵ�����ʾָ��ָ����µ�Ӧ�ó�������ݴ��ڡ����ݵĴ�С����ͨ��uip_len������á�	
 * \hideinitializer
 */
#define uip_newdata()   (uip_flags & UIP_NEWDATA)

/**
 * Has previously sent data been acknowledged?
 	��һ�����͵������յ���ACK?
 *
 * Will reduce to non-zero if the previously sent data has been
 * acknowledged by the remote host. This means that the application
 * can send new data.
 	ֵ�����ʾԶ��������������һ�����ݵ�ACK֡������ζ��Ӧ�ó�����Է�����һ�������ݡ�
 *
 * \hideinitializer
 */
#define uip_acked()   (uip_flags & UIP_ACKDATA)

/**
 * Has the connection just been connected?
 *	�����Ƿ񻹱������ӣ�

 * Reduces to non-zero if the current connection has been connected to
 * a remote host. This will happen both if the connection has been
 * actively opened (with uip_connect()) or passively opened (with
 * uip_listen()).
 	ֵ�����ʾ��ǰ������Ȼ������Զ�����������ӣ���ص������ӻ����Ĵ򿪻��߱����Ĵ򿪡� 	
 *
 * \hideinitializer
 */
#define uip_connected() (uip_flags & UIP_CONNECTED)

/**
 * Has the connection been closed by the other end?
 *	��һ�˵������Ƿ��նˣ�
 	
 * Is non-zero if the connection has been closed by the remote
 * host. The application may then do the necessary clean-ups.
 *	ֵ�����ʾ��Զ�����������ӱ��жϡ�Ӧ�ó��������Ҫ��һЩ��Ҫ����������
 * \hideinitializer
 */
#define uip_closed()    (uip_flags & UIP_CLOSE)

/**
 * Has the connection been aborted by the other end? 
 * 	��һ�˵������Ƿ��նˣ�

 * Non-zero if the current connection has been aborted (reset) by the
 * remote host.
 * 	ֵ�����ʾ��Զ�����������ӱ��жϣ����ã���
 * \hideinitializer
 */
#define uip_aborted()    (uip_flags & UIP_ABORT)

/**
 * Has the connection timed out?
 	���ӳ�ʱ��
 *
 * Non-zero if the current connection has been aborted due to too many
 * retransmissions.
 *	ֵ�����ʾ��ǰ��������̫���ش����������ж�
 * \hideinitializer
 */
#define uip_timedout()    (uip_flags & UIP_TIMEDOUT)

/**
 * Do we need to retransmit previously data?
 	�Ƿ���Ҫ�ش��ϴη�һ�����ݡ�
 *
 * Reduces to non-zero if the previously sent data has been lost in
 * the network, and the application should retransmit it. The
 * application should send the exact same data as it did the last
 * time, using the uip_send() function.
 *	ֵ�����ʾ��һ�����͵����ݶ�ʧ����̫���У�Ӧ�ó�����Ҫ�ش�����
 	Ӧ�ó���Ҫ������ͬ�����ݣ�ʹ��uip_send()������
 * \hideinitializer
 */
#define uip_rexmit()     (uip_flags & UIP_REXMIT)

/**
 * Is the connection being polled by uIP?
 	�����Ƿ���Ҫ����
 *
 * Is non-zero if the reason the application is invoked is that the
 * current connection has been idle for a while and should be
 * polled.		  
 	ֵ�����ʾӦ�ó�����鵱ǰ���ӵ�ԭ������Ϊ��������һ��ʱ����Ҫ���飨��ѯ����
 *
 * The polling event can be used for sending data without having to
 * wait for the remote host to send data.
 	��ѯ�¼������ڷ������ݣ������صȴ�Զ�������ȷ������ݡ�
 *
 * \hideinitializer
 */
#define uip_poll()       (uip_flags & UIP_POLL)

/**
 * Get the initial maxium segment size (MSS) of the current
 * connection.
 	��õ�ǰ���ӳ�ʼ������Ķδ�С
 *
 * \hideinitializer
 */
#define uip_initialmss()             (uip_conn->initialmss)

/**
 * Get the current maxium segment size that can be sent on the current
 * connection.
 	��ȡ��ǰ�����ܹ����͵�����ĶεĴ�С	
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
 	����һ���µ�UDP����
 *
 * This function sets up a new UDP connection. The function will
 * automatically allocate an unused local port for the new
 * connection. However, another port can be chosen by using the
 * uip_udp_bind() call, after the uip_udp_new() function has been
 * called.
 	�ú������ڽ���һ���µ�UDP���ӡ�����������Զ��ķ���һЩ�����õı��ض˿������µ����ӡ�
	Ȼ������һ���˿ڱ�uip_udp_bind()����ʹ�ã�֮������uip_udp_new()������
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
 * if no connection could be allocated.	 ����һ���µ����ӵĽṹ�壬�������û�з������ӣ����ؿ�
 */
struct uip_udp_conn *uip_udp_new(uip_ipaddr_t *ripaddr, u16_t rport);

/**
 * Removed a UDP connection.
 	ɾ��һ��UDP����
 *
 * \param conn A pointer to the uip_udp_conn structure for the connection.
 *
 * \hideinitializer
 */
#define uip_udp_remove(conn) (conn)->lport = 0

/**
 * Bind a UDP connection to a local port.
 	��һ��uDP���ӵ����ض˿�
 *
 * \param conn A pointer to the uip_udp_conn structure for the
 * connection.
 	��һ������ָ����UDP���ӵĽṹ���ָ��
 *
 * \param port The local port number, in network byte order.
 *
 * \hideinitializer
 */
#define uip_udp_bind(conn, port) (conn)->lport = port

/**
 * Send a UDP datagram of length len on the current connection.
 	����һ��len���ȵ�UDP���ݰ�����ǰ����
 *
 * This function can only be called in response to a UDP event (poll
 * or newdata). The data must be present in the uip_buf buffer, at the
 * place pointed to by the uip_appdata pointer.
	�������������ӦUDP�¼�ʱ�����á�Ҫ���͵����ݱ���������uip_buf�������У�
	��uip_appdataָ��ָ��ĵط���	
 *
 * \param len The length of the data in the uip_buf buffer.
 	���ݱ��ĳ��Ȳ�����uip_buf��������
 *
 * \hideinitializer
 */
#define uip_udp_send(len) uip_send((char *)uip_appdata, len)

/** @} */

/* uIP convenience and converting functions. 
	uip�����ת������*/

/**
 * \defgroup uipconvfunc uIP conversion functions ת������
 * @{
 *
 * These functions can be used for converting between different data
 * formats used by uIP.
 	��Щ�������������ڲ�ͬ�����ݸ�ʽ֮��ת��	
 */

/**
 * Construct an IP address from four bytes.����һ���ĸ��ֽڵ�IP��ַ
 *
 * This function constructs an IP address of the type that uIP handles
 * internally from four bytes. The function is handy for specifying IP
 * addresses to use with e.g. the uip_connect() function.
 	�����������һ��uIP��������ĸ��ֽڵ�IP��ַ�����������ʹ��uip_connect()�����ܷ���Ĵ���һ���̶���IP��ַ
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
 * 	����һ��ipv6�ĵ�ַ
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
 *	����һ��IP��ַ����һ��IP��ַ��
 * Copies an IP address from one place to another.
 * 	����һ��IP��ַ�ĸ�������һ���ط�
 * Example:
 \code
 uip_ipaddr_t ipaddr1, ipaddr2;

 uip_ipaddr(&ipaddr1, 192,16,1,2);
 uip_ipaddr_copy(&ipaddr2, &ipaddr1);
 \endcode
 *
 * \param dest The destination for the copy.���ڿ������ܵ�Ŀ�Ĳ���
 * \param src The source from where to copy.���ڿ������ܵ�Դ����
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
 	�Ƚ�����IP��ַ�Ƿ����
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
 	ʹ������Ƚ�����IP��ַ
 *
 * Compares two IP addresses with netmasks. The masks are used to mask
 * out the bits that are to be compared.
 	ʹ������Ƚ�����IP��ַ�����������������һЩλȻ��Ƚϣ�����ȷ��������ַ�Ƿ���ͬһ����
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
	�õ�һ��IP��ַ������
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
 	ѡ��IP��ַ�ĵ�һ���ֽ�
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
 	ѡ��IP��ַ�ĵڶ����ֽ�
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
 	ѡ��IP��ַ�ĵ������ֽ�
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
 	ѡ��IP��ַ�ĵ��ĸ��ֽ�
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
 	��16λ���ִ������ֽ�˳��ת��Ϊ�����ֽ�˳��
 *
 * This macro is primarily used for converting constants from host
 * byte order to network byte order. For converting variables to
 * network byte order, use the htons() function instead.
 	�������Ҫʹ����һ�������������ֽ�˳��ת��Ϊ�����ֽ�˳�����Ҫ������ת��Ϊ�����ֽ�˳��
	��Ҫʹ��htons()��������ת����
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
	��16λ���ִ������ֽ�˳��ת��Ϊ�����ֽ�˳��
 *
 * This function is primarily used for converting variables from host
 * byte order to network byte order. For converting constants to
 * network byte order, use the HTONS() macro instead.
 	�������Ҫ��������һ�������������ֽ�˳��ת��Ϊ�����ֽ�˳��ת��������Ҫʹ��HTONS()��
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
 	ָ���Ļ�������Ӧ�ó������ݵ�ָ��
 *
 * This pointer points to the application data when the application is
 * called. If the application wishes to send data, the application may
 * use this space to write the data into before calling uip_send().
 	��������������õ�ʱ��ָ��ָ��Ӧ�ó�������ݱ��ġ�������������Ҫ�������ݣ�
	�ڵ���uip_send()��������֮ǰ����Ҫָ��Ŀռ�д���Ĳ��С�
 */
extern void *uip_appdata;

#if UIP_URGDATA > 0
/* u8_t *uip_urgdata:
 *
 * This pointer points to any urgent data that has been received. Only
 * present if compiled with support for urgent data (UIP_URGDATA).
 	���ָ��ָ���κν��յ���urgent���ݱ��ġ�ֻ��ѡ�������urgent data����ܣ����ָ��Ŵ��ڡ�
 */
extern void *uip_urgdata;
#endif /* UIP_URGDATA > 0 */


/**
 * \defgroup uipdrivervars Variables used in uIP device drivers
	uip��uipdriervars�����������豸���� 	
 * @{
 *
 * uIP has a few global variables that are used in device drivers for
 * uIP.
 	��uipЭ����ֻ�ṩ�ͺ��ٵĵ�ȫ�ֱ������豸����ʹ��
 */

/**
 * The length of the packet in the uip_buf buffer.
 	uip_buf�������б��ĵĳ���
 *
 * The global variable uip_len holds the length of the packet in the
 * uip_buf buffer.			 
 	���ȫ�ֱ���uip_len�����˱��Ļ������б��ĵĳ���
 *
 * When the network device driver calls the uIP input function,
 * uip_len should be set to the length of the packet in the uip_buf
 * buffer.
 	�������豸�������򱻵��ã��ñ���Ӧ��������Ϊ���Ļ������б��ĵĳ���ֵ
 *
 * When sending packets, the device driver should use the contents of
 * the uip_len variable to determine the length of the outgoing
 * packet.
 	����Ҫ���ͱ���ʱ���豸����������Ҫ������uip_len��ֵ���Ѿ���Ӧ�����͵ı��Ķεĳ����Ƕ��١�
 *
 */
extern u16_t uip_len;

/** @} */

#if UIP_URGDATA > 0
extern u16_t uip_urglen, uip_surglen;
#endif /* UIP_URGDATA > 0 */


/**
 * Representation of a uIP TCP connection.
 	��ʾһ��TCP����
 *
 * The uip_conn structure is used for identifying a connection. All
 * but one field in the structure are to be considered read-only by an
 * application. The only exception is the appstate field whos purpose
 * is to let the application store application-specific state (e.g.,
 * file pointers) for the connection. The type of this field is
 * configured in the "uipopt.h" header file.
 */
struct uip_conn {
  uip_ipaddr_t ripaddr;   /**< The IP address of the remote host. Զ�������ĵ�ַ*/

  u16_t lport;        /**< The local TCP port, in network byte order. ����������TCP�˿ںţ�ʹ�������ֽ�˳��*/
  u16_t rport;        /**< The local remote TCP port, in network byte
			 order. Զ��������TCP�˿ںţ�ʹ�������ֽ�˳��*/
/* ���մ����п��Խ��յ���һ�ֽ����*/
  u8_t rcv_nxt[4];    /**< The sequence number that we expect to
			 receive next. �ڴ����յ���һ���ֽڵ����*/
/* ���ʹ�������һ��Ҫ�����ֽڵ����*/			 	
  u8_t snd_nxt[4];    /**< The sequence number that was last sent by
                         us. */
/*���ʹ������Ѿ����͵�δ��ȷ�ϰ��ĳ���*/						 	
  u16_t len;          /**< Length of the data that was previously sent. ǰһ�������͵ı��ĵĳ���*/
  u16_t mss;          /**< Current maximum segment size for the
			 connection. ��ǰ�����ܷ��͵�����ĶεĴ�С*/
  u16_t initialmss;   /**< Initial maximum segment size for the
			 connection. ��ʼ������Ķδ�С*/
  u8_t sa;            /**< Retransmission time-out calculation state
			 variable. ������Ҫ�ش���ʱ��ʱ��*/
  u8_t sv;            /**< Retransmission time-out calculation state
			 variable. */
/*�ط���ʱֵ*/			 	
  u8_t rto;           /**< Retransmission time-out. �ط���ʱֵ*/
  u8_t tcpstateflags; /**< TCP state and flags. ״̬��ʶ*/
/* ÿ��perodic timer��ʱʱtimer-- ,��uip_proecess() */  
  u8_t timer;         /**< The retransmission timer. */
  /* ��һ�������ط�����*/
  u8_t nrtx;          /**< The number of retransmissions for the last
			 segment sent. ��һ�����Ķ��ش��Ĵ���*/

  /** The application state. �û�����״̬��ʶ*/
  uip_tcp_appstate_t appstate;
};


/**
 * Pointer to the current TCP connection.	��ǰTCP���ӵ�ָ��
 *
 * The uip_conn pointer can be used to access the current TCP
 * connection.
 	���ָ������������ʵ�ǰTCP����
 */
extern struct uip_conn *uip_conn;
/* The array containing all uIP connections. 
	���������������е�UIPЭ��ջ�����ӣ�Ĭ������Ϊ���������40*/
extern struct uip_conn uip_conns[UIP_CONNS];
/**
 * \addtogroup uiparch
 * @{
 */

/**
 * 4-byte array used for the 32-bit sequence number calculations.
 	4���ֽڵ�������������32λ���к�
 */
extern u8_t uip_acc32[4];

/** @} */


#if UIP_UDP
/**
 * Representation of a uIP UDP connection.
 	��ʾUDP��������
 */
struct uip_udp_conn {
  uip_ipaddr_t ripaddr;   /**< The IP address of the remote peer. Զ�̶Եȵ�IP��ַ*/
  u16_t lport;        /**< The local port number in network byte order. ���ض˿ںţ�ʹ�������ֽ�˳��*/
  u16_t rport;        /**< The remote port number in network byte order. Զ�������˿ںţ�ʹ�������ֽ�˳��*/
  u8_t  ttl;          /**< Default time-to-live. Ĭ������ʱ��*/

  /** The application state. Ӧ�ó���״̬��ǩ*/
  uip_udp_appstate_t appstate;
};

/**
 * The current UDP connection. ��ǰ����
 */
extern struct uip_udp_conn *uip_udp_conn;
extern struct uip_udp_conn uip_udp_conns[UIP_UDP_CONNS];
#endif /* UIP_UDP */

/**
 * The structure holding the TCP/IP statistics that are gathered if
 * UIP_STATISTICS is set to 1.
 	��UIP_STATISTICS������Ϊ1������ͳ����
 *
 */
struct uip_stats {
  struct {
    uip_stats_t recv;     /**< Number of received packets at the IP
			     layer. IP����յ��İ�������*/
    uip_stats_t sent;     /**< Number of sent packets at the IP
			     layer. IP�㷢�͵İ�������*/
    uip_stats_t drop;     /**< Number of dropped packets at the IP
			     layer. IP�㶪���İ�������*/
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
 * The uIP TCP/IP statistics. TCP/IIPͳ��
 *
 * This is the variable in which the uIP TCP/IP statistics are gathered.�������������TCP/IPͳ����Ϣ��
 */
extern struct uip_stats uip_stat;


/*---------------------------------------------------------------------------*/
/* All the stuff below this point is internal to uIP and should not be
 * used directly by an application or by a device driver.���µ����еĶ�������Ӧ����Ӧ�ó�����豸����ֱ�ӵ���
 */
/*---------------------------------------------------------------------------*/
/* u8_t uip_flags:
 *
 * When the application is called, uip_flags will contain the flags
 * that are defined in this file. Please read below for more
 * infomation.
 	��Ӧ�ó��򱻵����ǣ�uip_flags����������ļ������Ķ����¸�����Ϣ
 */
extern u8_t uip_flags;

/* The following flags may be set in the global variable uip_flags
   before calling the application callback. The UIP_ACKDATA,
   UIP_NEWDATA, and UIP_CLOSE flags may both be set at the same time,
   whereas the others are mutualy exclusive. Note that these flags
   should *NOT* be accessed directly, but only through the uIP
   functions/macros. 
   	����ı�ʶuip_flags���ܱ�����Ϊȫ�ֱ������ڵ���Ӧ�ó���֮ǰ���ء�
	UIP_ACKDATA,UIP_NEWDATA,UIP_CLOSE��ʶ���ܻ�ͬʱ�����ã����ܻᱻxx�ų⡣
	��Ҫע�������Щ��ʶ��Ӧ�ñ�ֱ�ӷ��ʣ�ֻ��ͨ��UIPЭ��ջ���������ʡ�*/

/*���ʹ�����δ��ȷ�ϵ������Ѿ��õ�ȷ��, ���Է��������ݶ������ط�*/
#define UIP_ACKDATA   1     /* Signifies that the outstanding data was
			       acked and the application should send
			       out new data instead of retransmitting
			       the last data. */
/* ���յ��İ��ﺬ���û�����*/			       
#define UIP_NEWDATA   2     /* Flags the fact that the peer has sent
			       us new data. */
#define UIP_REXMIT    4     /* Tells the application to retransmit the
			       data that was last sent. ����Ӧ�ó����ش���һ������*/
#define UIP_POLL      8     /* Used for polling the application, to
			       check if the application has data that
			       it wants to send. ������ѯ�û����򣬼��Ӧ�ó����Ƿ���Ҫ���ͱ���*/
#define UIP_CLOSE     16    /* The remote host has closed the
			       connection, thus the connection has
			       gone away. Or the application signals
			       that it wants to close the
			       connection. Զ�������ر������ӣ����������Ҫ�����������û�����ʹ������źţ���ر��������*/
#define UIP_ABORT     32    /* The remote host has aborted the
			       connection, thus the connection has
			       gone away. Or the application signals
			       that it wants to abort the
			       connection. Զ�������ж������ӣ�������Ӷ����������û�������Ҫ�ն�����*/
/*һ�������Ѿ�����������(������ESTABLISHED״̬)*/			      
#define UIP_CONNECTED 64    /* We have got a connection from a remote
                               host and have set up a new connection
                               for it, or an active connection has
                               been successfully established. 
							   	��ѯһ�������Ƿ񱻽������Ƿ��Ծ*/

#define UIP_TIMEDOUT  128   /* The connection has been aborted due to
			       too many retransmissions. �����Ƿ������ش���ʱ���ն�*/

/* uip_process(flag):
 *
 * The actual uIP function which does all the work.
 	�����յ������ǣ��ó�������uip_udp_conns���飬�������Ŀ�Ķ˿�
	�뱾���˿ڲ�ƥ�䣬����Զ�̶˿���uip_udp_new�еĶ˿ڲ�ƥ�䣬uip��
	ֱ�Ӷ����������
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
				   global variable uip_len. ����UIP������һ����*/
#define UIP_TIMER         2     /* Tells uIP that the periodic timer
				   has fired. ����UP���ڶ�ʱ��ʧЧ*/
#define UIP_POLL_REQUEST  3     /* Tells uIP that a connection should
				   be polled. ����UIP������Ҫ�����*/
#define UIP_UDP_SEND_CONN 4     /* Tells uIP that a UDP datagram
				   should be constructed in the
				   uip_buf buffer. ����UIP��Ҫ����һ��UDP����֡���ڻ�������*/
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

/* The TCP and IP headers. TCPЭ���IP����ͷ*/
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
    tcpoffset,	/*ǰ4λ��TCP�ײ�����*/
    flags,		/*��6λ��TCP����־λ*/
    wnd[2];
  u16_t tcpchksum;
  u8_t urgp[2];
  u8_t optdata[4];
};

/* The ICMP and IP headers. ICMPЭ���IP���ĵ�ͷ*/
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
    len[2],		/*16λ��IP���ܳ���, ����IPͷ+TCP��, ����FCS*/
    ipid[2],	/* 16λ��IP����ʶ*/
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
 *	�����������С�����������û����Ļ�������

 * This macro holds the available size for user data in the \ref
 * uip_buf buffer. The macro is intended to be used for checking
 * bounds of available user data.
 	����걣�����û����������Ĵ�С���á�Ŀ���Ǽ��Լ���û�����
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
#define UIP_IPH_LEN    20    /* Size of IP header IP����ͷ�Ĵ�С*/
#endif /* UIP_CONF_IPV6 */
#define UIP_UDPH_LEN    8    /* Size of UDP header UDP����ͷ�Ĵ�С*/
#define UIP_TCPH_LEN   20    /* Size of TCP header TCP����ͷ�Ĵ�С*/
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
 * Calculate the Internet checksum over a buffer.����������У���
 *
 * The Internet checksum is the one's complement of the one's
 * complement sum of all 16-bit words in the buffer.
 	Ӣ����У����ǲ���
 *
 * See RFC1071.
 *
 * \param buf A pointer to the buffer over which the checksum is to be
 * computed.  ��Ҫ����У��͵�buffer
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
