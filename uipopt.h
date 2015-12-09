/**
 * \defgroup uipopt Configuration options for uIP
 * @{
 *
 * uIP is configured using the per-project configuration file
 * uipopt.h. This file contains all compile-time options for uIP and
 * should be tweaked to match each specific project. The uIP
 * distribution contains a documented example "uipopt.h" that can be
 * copied and modified for each project.
 *
 * \note Most of the configuration options in the uipopt.h should not
 * be changed, but rather the per-project uip-conf.h file.
 */

/**
 * \file
 * Configuration options for uIP.
 * \author Adam Dunkels <adam@dunkels.com>
 *
 * This file is used for tweaking various configuration options for
 * uIP. You should make a copy of this file into one of your project's
 * directories instead of editing this example "uipopt.h" file that
 * comes with the uIP distribution.
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
 * $Id: uipopt.h 22899 2008-06-10 09:23:10Z anderslu $
 *
 */

#ifndef __UIPOPT_H__
#define __UIPOPT_H__

#ifndef UIP_LITTLE_ENDIAN
#define UIP_LITTLE_ENDIAN  3412
#endif /* UIP_LITTLE_ENDIAN */
#ifndef UIP_BIG_ENDIAN
#define UIP_BIG_ENDIAN     1234
#endif /* UIP_BIG_ENDIAN */

#include "uip-conf.h"

/*------------------------------------------------------------------------------*/

/**
 * \name Static configuration options ��̬����ѡ��
 * @{
 *
 * These configuration options can be used for setting the IP address
 * settings statically, but only if UIP_FIXEDADDR is set to 1. The
 * configuration options for a specific node includes IP address,
 * netmask and default router as well as the Ethernet address. The
 * netmask, default router and Ethernet address are appliciable only
 * if uIP should be run over Ethernet.
 *
 * All of these should be changed to suit your project.
 * ��Щ����ѡ���ܹ����þ�̬IP��ַ����ֻ��FIXEDADDR����Ϊ1��ʱ�����Ч��
 * ��һ���ض��ڵ������ѡ�����IP��ַ�����ص�ַ��Ĭ��·������ַ�Լ���̫����ַ��
 * ��ЩĬ�ϵ�����ֻ����UIPЭ����������̫���ǲ����á�
*/

/**
 * Determines if uIP should use a fixed IP address or not. ȷ���Ƿ�ʹ�ù̶���IP��ַ
 *
 * If uIP should use a fixed IP address, the settings are set in the
 * uipopt.h file. If not, the macros uip_sethostaddr(),
 * uip_setdraddr() and uip_setnetmask() should be used instead.
 * ���UIPʹ�ù̶���IP��ַ����Ҫ�޸�uipopt.h�ļ���������ǹ̶���ַ�����º���Ҫ������
 * \hideinitializer
 */
#define UIP_FIXEDADDR    0

/**
 * Ping IP address asignment.
 *
 * uIP uses a "ping" packets for setting its own IP address if this
 * option is set. If so, uIP will start with an empty IP address and
 * the destination IP address of the first incoming "ping" (ICMP echo)
 * packet will be used for setting the hosts IP address.
 * UIPʹ��һ��ping�������Լ���ip��ַ�������������õĻ���
 * ��ˣ�һ��ʼUIP������һ���յ�ip��ַ������Ŀ�ĵ�ַ�ᱻ����Ϊ��һ��'ping'��Ӧ���ĵĵ�������ַ
 * \note This works only if UIP_FIXEDADDR is 0. ����FIXEDADDRΪ0�ǲ�������
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_PINGADDRCONF
#define UIP_PINGADDRCONF UIP_CONF_PINGADDRCONF
#else /* UIP_CONF_PINGADDRCONF */
#define UIP_PINGADDRCONF 1
#endif /* UIP_CONF_PINGADDRCONF */


/**
 * Specifies if the uIP ARP module should be compiled with a fixed
 * Ethernet MAC address or not.
 * �ر�ģ����ARPģ��Ҫ������Ҫ�̶���̫��MAC��ַ
 * If this configuration option is 0, the macro uip_setethaddr() can
 * be used to specify the Ethernet address at run-time.
 * ����������ѡ��Ϊ0����Ҫ������ʱ���ú�uip_setehaddr()��ָ����̫����ַ
 * \hideinitializer
 */
#define UIP_FIXEDETHADDR 1

#define UIP_ETHADDR0    0x00  /**< The first octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR1    0x4f  /**< The second octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR2    0x49  /**< The third octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR3    0x12  /**< The fourth octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR4    0x12  /**< The fifth octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer */
#define UIP_ETHADDR5    0x13  /**< The sixth octet of the Ethernet
				 address if UIP_FIXEDETHADDR is
				 1. \hideinitializer ��������λ����̫����ַ*/


/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \name IP configuration options ip����ѡ��
 * @{
 *
 */
/**
 * The IP TTL (time to live) of IP packets sent by uIP.
 * ip���ݰ�����������
 * This should normally not be changed. ͨ�����ı����ֵ
 */
#define UIP_TTL         64

/**
 * Turn on support for IP packet reassembly.�򿪸�ѡ����֧��ip���ݰ�����װ����
 * 
 * uIP supports reassembly of fragmented IP packets. This features
 * requires an additonal amount of RAM to hold the reassembly buffer
 * and the reassembly code size is approximately 700 bytes.  The
 * reassembly buffer is of the same size as the uip_buf buffer
 * (configured by UIP_BUFSIZE).
 * Э��֧�ַ�ɢ��ip���ݰ�����װ�����������Ҫ���Ķ�����ڴ棬������������װ���ĵĻ����Լ���װ���ܴ���飬������Ҫ700�ֽڵĶ����ڴ档
 * ͨ������װ���������С��uip_buf���á�
 * \note IP packet reassembly is not heavily tested. ip���ݰ���װ����δ�����ϸ����
 *
 * \hideinitializer
 */
#define UIP_REASSEMBLY 0	//IP���ݰ�����װ�ع���

/**
 * The maximum time an IP fragment should wait in the reassembly
 * buffer before it is dropped.
 * IPƬ�ζ���֮ǰ����װ�������ȴ���ʱ��
 */
#define UIP_REASS_MAXAGE 40

/** @} */

/*------------------------------------------------------------------------------*/
/**
 * \name UDP configuration options UDP����ѡ��
 * @{
 */

/**
 * Toggles wether UDP support should be compiled in or not.	�Ƿ����udp����
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP
#define UIP_UDP UIP_CONF_UDP
#else /* UIP_CONF_UDP */
#define UIP_UDP           0
#endif /* UIP_CONF_UDP */

/**
 * Toggles if UDP checksums should be used or not. �����Ƿ�ʹ��udpУ��͹���
 *
 * \note Support for UDP checksums is currently not included in uIP,
 * so this option has no function. ĿǰudpУ��͹��ܲ�������uipЭ��ջ�У�
 * ������ѡ���޷��ﵽ����
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP_CHECKSUMS
#define UIP_UDP_CHECKSUMS UIP_CONF_UDP_CHECKSUMS
#else
#define UIP_UDP_CHECKSUMS 0
#endif

/**
 * The maximum amount of concurrent UDP connections. ����UDP���ӵ��������
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP_CONNS
#define UIP_UDP_CONNS UIP_CONF_UDP_CONNS
#else /* UIP_CONF_UDP_CONNS */
#define UIP_UDP_CONNS    10
#endif /* UIP_CONF_UDP_CONNS */

/**
 * The name of the function that should be called when UDP datagrams arrive.
 * ��UDP���ݰ�����ʱ�������Ӧ��������
 * \hideinitializer
 */


/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \name TCP configuration options 
 * @{
 */

/**
 * Determines if support for opening connections from uIP should be
 * compiled in.
 *
 * If the applications that are running on top of uIP for this project
 * do not need to open outgoing TCP connections, this configration
 * option can be turned off to reduce the code size of uIP.
 *
 * \hideinitializer
 */
#define UIP_ACTIVE_OPEN 0	/*�Ƿ�����������*/

/**
 * The maximum number of simultaneously open TCP connections. ͬʱ��TCP���ӵ������ֵ
 *
 * Since the TCP connections are statically allocated, turning this
 * configuration knob down results in less RAM used. Each TCP
 * connection requires approximatly 30 bytes of memory.
 * ����TCP�����Ǿ�̬����ģ���˰����������������ڽ�ʡ�ڴ档
 * ÿ��TCP���Ӵ�����Ҫ30���ֽڵ��ڴ档
 * \hideinitializer
 */
#ifndef UIP_CONF_MAX_CONNECTIONS
#define UIP_CONNS       10
#else /* UIP_CONF_MAX_CONNECTIONS */
#define UIP_CONNS UIP_CONF_MAX_CONNECTIONS
#endif /* UIP_CONF_MAX_CONNECTIONS */


/**
 * The maximum number of simultaneously listening TCP ports. ͬʱ����TCP�˿ڵ������ֵ
 *
 * Each listening TCP port requires 2 bytes of memory. ÿ����һ��TCP�˿���Ҫ2�ֽڵ��ڴ�
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_MAX_LISTENPORTS
#define UIP_LISTENPORTS 20
#else /* UIP_CONF_MAX_LISTENPORTS */
#define UIP_LISTENPORTS UIP_CONF_MAX_LISTENPORTS
#endif /* UIP_CONF_MAX_LISTENPORTS */

/**
 * Determines if support for TCP urgent data notification should be
 * compiled in. �Ƿ�֧��TCP�������ݰ�ͨ��
 *
 * Urgent data (out-of-band data) is a rarely used TCP feature that
 * very seldom would be required.�ù��ܺ��ٱ�ʹ�õ�
 *
 * \hideinitializer
 */
#define UIP_URGDATA      0

/**
 * The initial retransmission timeout counted in timer pulses.
 *
 * This should not be changed. ��ֵ����Ҫ�䶯
 */
#define UIP_RTO         3

/**
 * The maximum number of times a segment should be retransmitted
 * before the connection should be aborted.һ����������ش����ٴβ�ȡ������
 *
 * This should not be changed.
 */
#define UIP_MAXRTX      8

/**
 * The maximum number of times a SYN segment should be retransmitted
 * before a connection request should be deemed to have been
 * unsuccessful.һ��SYN��������ش����ٴβ��϶���������ʧ��
 *
 * This should not need to be changed.
 */
#define UIP_MAXSYNRTX      5

/**
 * The TCP maximum segment size.
 * TCP������С
 * This is should not be to set to more than
 * UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN. ��Ҫ���ó��������С��ֵ 
 */
#define UIP_TCP_MSS     (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)

/**
 * The size of the advertised receiver's window.
 * ���մ��ڵĴ�С
 * Should be set low (i.e., to the size of the uip_buf buffer) is the
 * application is slow to process incoming data, or high (32768 bytes)
 * if the application processes data quickly.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_RECEIVE_WINDOW
#define UIP_RECEIVE_WINDOW UIP_TCP_MSS
#else
#define UIP_RECEIVE_WINDOW UIP_CONF_RECEIVE_WINDOW
#endif

/**
 * How long a connection should stay in the TIME_WAIT state.
 * ��õ���������ͣ����TIME_WAIT״̬
 * This configiration option has no real implication, and it should be
 * left untouched.���ѡ��û��ʵ�����壬Ӧ�����ֲ���
 */
#define UIP_TIME_WAIT_TIMEOUT 120


/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \name ARP configuration options
 * @{
 */

/**
 * The size of the ARP table.
 * ARP��Ĵ�С
 * This option should be set to a larger value if this uIP node will
 * have many connections from the local network.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_ARPTAB_SIZE
#define UIP_ARPTAB_SIZE UIP_CONF_ARPTAB_SIZE
#else
#define UIP_ARPTAB_SIZE 8
#endif

/**
 * The maxium age of ARP table entries measured in 10ths of seconds.
 * 
 * An UIP_ARP_MAXAGE of 120 corresponds to 20 minutes (BSD
 * default).
 */
#define UIP_ARP_MAXAGE 120

/** @} */

/*------------------------------------------------------------------------------*/

/**
 * \name General configuration options
 * @{
 */

/**
 * The size of the uIP packet buffer.
 * uip���ݰ��������Ĵ�С
 * The uIP packet buffer should not be smaller than 60 bytes, and does
 * not need to be larger than 1500 bytes. Lower size results in lower
 * TCP throughput, larger size results in higher TCP throughput.
 * uip���ݰ���������СӦ����С��60�ֽڣ�������1500�ֽڣ�������Խ��TCP��������Խ��
 * \hideinitializer
 */
#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_BUFSIZE     1520	/*ԭʼuipΪ400*/
#else /* UIP_CONF_BUFFER_SIZE */
#define UIP_BUFSIZE UIP_CONF_BUFFER_SIZE
#endif /* UIP_CONF_BUFFER_SIZE */


/**
 * Determines if statistics support should be compiled in. �Ƿ�֧�ֱ���ͳͳ�ƹ���
 *
 * The statistics is useful for debugging and to show the user. ͳ�ƹ��ܶ��ڵ��Էǳ�����
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_STATISTICS
#define UIP_STATISTICS  1
#else /* UIP_CONF_STATISTICS */
#define UIP_STATISTICS UIP_CONF_STATISTICS
#endif /* UIP_CONF_STATISTICS */

/**
 * Determines if logging of certain events should be compiled in. ȷ��ĳЩ�¼�����־�����Ƿ����
 *
 * This is useful mostly for debugging. The function uip_log()
 * must be implemented to suit the architecture of the project, if
 * logging is turned on.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_LOGGING
#define UIP_LOGGING     0
#else /* UIP_CONF_LOGGING */
#define UIP_LOGGING     UIP_CONF_LOGGING
#endif /* UIP_CONF_LOGGING */

/**
 * Broadcast support. �㲥�����Ƿ�֧��
 *
 * This flag configures IP broadcast support. This is useful only
 * together with UDP. �����ʶ����ip�㲥�����Ƿ�֧�֣�����UDP������
 *
 * \hideinitializer
 *
 */
#ifndef UIP_CONF_BROADCAST
#define UIP_BROADCAST 0
#else /* UIP_CONF_BROADCAST */
#define UIP_BROADCAST UIP_CONF_BROADCAST
#endif /* UIP_CONF_BROADCAST */

/**
 * Print out a uIP log message.	��ӡ��־��Ϣ
 *
 * This function must be implemented by the module that uses uIP, and
 * is called by uIP whenever a log message is generated. 
 * ����ʵ�����ģ�飬�ù��ܲ���ʹ��
 */
void uip_log(char *msg);

/**
 * The link level header length.
 * ��·��ͷ�ĳ���
 * This is the offset into the uip_buf where the IP header can be
 * found. For Ethernet, this should be set to 14. For SLIP, this
 * should be set to 0.
 * ����һ��uip_buf��ƫ�����������ҵ�IP���ݰ��ı�ͷ��ͨ��Ӧ������Ϊ14�����ڻ�����˵���ֵӦ��������Ϊ0
 * \hideinitializer
 */
 /*IP����������̫��֡�е���ʼ��ַ*/
#ifdef UIP_CONF_LLH_LEN
#define UIP_LLH_LEN UIP_CONF_LLH_LEN
#else /* UIP_CONF_LLH_LEN */
#define UIP_LLH_LEN     14	/*��̫��֡ͷ��14�ֽ�*/
#endif /* UIP_CONF_LLH_LEN */

/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \name CPU architecture configuration CPU�ܹ�����
 * @{
 *
 * The CPU architecture configuration is where the endianess of the
 * CPU on which uIP is to be run is specified. Most CPUs today are
 * little endian, and the most notable exception are the Motorolas
 * which are big endian. The BYTE_ORDER macro should be changed to
 * reflect the CPU architecture on which uIP is to be run.
 */

/**
 * The byte order of the CPU architecture on which uIP is to be run.
 * 
 * This option can be either BIG_ENDIAN (Motorola byte order) or
 * LITTLE_ENDIAN (Intel byte order).
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_BYTE_ORDER	//ȷ��cpu��ʹ�ô��ģʽ����С��ģʽ
#define UIP_BYTE_ORDER     UIP_CONF_BYTE_ORDER
#else /* UIP_CONF_BYTE_ORDER */
#define UIP_BYTE_ORDER     UIP_LITTLE_ENDIAN
#endif /* UIP_CONF_BYTE_ORDER */

/** @} */
/*------------------------------------------------------------------------------*/

/**
 * \name Appication specific configurations Ӧ�ó����������
 * @{
 *
 * An uIP application is implemented using a single application
 * function that is called by uIP whenever a TCP/IP event occurs. The
 * name of this function must be registered with uIP at compile time
 * using the UIP_APPCALL definition.
 * ʵ��һ���򵥵�uipӦ�ó��򣬵�����TCP/IP�¼�ʱͨ��uipЭ���������
 * ��������������ڱ���ʱ����Ҫ��APPCALL��ǩ����
 * uIP applications can store the application state within the
 * uip_conn structure by specifying the type of the application
 * structure by typedef:ing the type uip_tcp_appstate_t and uip_udp_appstate_t.
 *
 * The file containing the definitions must be included in the
 * uipopt.h file.
 *
 * The following example illustrates how this can look.
 \code

void httpd_appcall(void);
#define UIP_APPCALL     httpd_appcall

struct httpd_state {
  u8_t state;
  u16_t count;
  char *dataptr;
  char *script;
};
typedef struct httpd_state uip_tcp_appstate_t
 \endcode
 */

/**
 * \var #define UIP_APPCALL
 *
 * The name of the application function that uIP should call in
 * response to TCP/IP events.
 *
 */

/**
 * \var typedef uip_tcp_appstate_t
 *
 * The type of the application state that is to be stored in the
 * uip_conn structure. This usually is typedef:ed to a struct holding
 * application state information.
 */

/**
 * \var typedef uip_udp_appstate_t
 *
 * The type of the application state that is to be stored in the
 * uip_conn structure. This usually is typedef:ed to a struct holding
 * application state information.
 */
/** @} */
/** @} */

#endif /* __UIPOPT_H__ */
