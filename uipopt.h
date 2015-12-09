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
 * \name Static configuration options 静态配置选项
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
 * 这些配置选项能够设置静态IP地址，但只有FIXEDADDR设置为1的时候才有效。
 * 对一个特定节点的配置选项，包括IP地址，网关地址和默认路由器地址以及以太网地址。
 * 这些默认的配置只有在UIP协议运行在以太网是才有用。
*/

/**
 * Determines if uIP should use a fixed IP address or not. 确定是否使用固定的IP地址
 *
 * If uIP should use a fixed IP address, the settings are set in the
 * uipopt.h file. If not, the macros uip_sethostaddr(),
 * uip_setdraddr() and uip_setnetmask() should be used instead.
 * 如果UIP使用固定的IP地址，将要修改uipopt.h文件。如果不是固定地址，以下宏需要被设置
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
 * UIP使用一个ping包设置自己的ip地址，如果这项功能启用的话。
 * 因此，一开始UIP将会有一个空的ip地址，并且目的地址会被设置为第一个'ping'回应报文的的主机地址
 * \note This works only if UIP_FIXEDADDR is 0. 仅当FIXEDADDR为0是才起作用
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
 * 特别的，如果ARP模块要编译需要固定以太网MAC地址
 * If this configuration option is 0, the macro uip_setethaddr() can
 * be used to specify the Ethernet address at run-time.
 * 如果这个配置选项为0，需要在运行时调用宏uip_setehaddr()来指定以太网地址
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
				 1. \hideinitializer 第六个八位的以太网地址*/


/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \name IP configuration options ip配置选项
 * @{
 *
 */
/**
 * The IP TTL (time to live) of IP packets sent by uIP.
 * ip数据包的生存周期
 * This should normally not be changed. 通常不改变这个值
 */
#define UIP_TTL         64

/**
 * Turn on support for IP packet reassembly.打开该选项以支持ip数据包的重装功能
 * 
 * uIP supports reassembly of fragmented IP packets. This features
 * requires an additonal amount of RAM to hold the reassembly buffer
 * and the reassembly code size is approximately 700 bytes.  The
 * reassembly buffer is of the same size as the uip_buf buffer
 * (configured by UIP_BUFSIZE).
 * 协议支持分散的ip数据包的重装。这个功能需要消耗额外的内存，以用来保存重装报文的缓存以及重装功能代码块，大致需要700字节的额外内存。
 * 通样的重装缓存变量大小由uip_buf设置。
 * \note IP packet reassembly is not heavily tested. ip数据包重装功能未经过严格测试
 *
 * \hideinitializer
 */
#define UIP_REASSEMBLY 0	//IP数据包的重装载功能

/**
 * The maximum time an IP fragment should wait in the reassembly
 * buffer before it is dropped.
 * IP片段丢弃之前在重装缓冲区等待的时间
 */
#define UIP_REASS_MAXAGE 40

/** @} */

/*------------------------------------------------------------------------------*/
/**
 * \name UDP configuration options UDP配置选项
 * @{
 */

/**
 * Toggles wether UDP support should be compiled in or not.	是否编译udp功能
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP
#define UIP_UDP UIP_CONF_UDP
#else /* UIP_CONF_UDP */
#define UIP_UDP           0
#endif /* UIP_CONF_UDP */

/**
 * Toggles if UDP checksums should be used or not. 决定是否使用udp校验和功能
 *
 * \note Support for UDP checksums is currently not included in uIP,
 * so this option has no function. 目前udp校验和功能不包括在uip协议栈中，
 * 因此这个选项无法达到功能
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP_CHECKSUMS
#define UIP_UDP_CHECKSUMS UIP_CONF_UDP_CHECKSUMS
#else
#define UIP_UDP_CHECKSUMS 0
#endif

/**
 * The maximum amount of concurrent UDP connections. 并发UDP连接的最大数量
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
 * 当UDP数据包到达时这个函数应当被调用
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
#define UIP_ACTIVE_OPEN 0	/*是否允许主动打开*/

/**
 * The maximum number of simultaneously open TCP connections. 同时打开TCP连接的最大数值
 *
 * Since the TCP connections are statically allocated, turning this
 * configuration knob down results in less RAM used. Each TCP
 * connection requires approximatly 30 bytes of memory.
 * 由于TCP连接是静态分配的，因此把连接数调低有利于节省内存。
 * 每个TCP连接大致需要30个字节的内存。
 * \hideinitializer
 */
#ifndef UIP_CONF_MAX_CONNECTIONS
#define UIP_CONNS       10
#else /* UIP_CONF_MAX_CONNECTIONS */
#define UIP_CONNS UIP_CONF_MAX_CONNECTIONS
#endif /* UIP_CONF_MAX_CONNECTIONS */


/**
 * The maximum number of simultaneously listening TCP ports. 同时监听TCP端口的最大数值
 *
 * Each listening TCP port requires 2 bytes of memory. 每监听一个TCP端口需要2字节的内存
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
 * compiled in. 是否支持TCP紧急数据包通信
 *
 * Urgent data (out-of-band data) is a rarely used TCP feature that
 * very seldom would be required.该功能很少被使用到
 *
 * \hideinitializer
 */
#define UIP_URGDATA      0

/**
 * The initial retransmission timeout counted in timer pulses.
 *
 * This should not be changed. 该值不需要变动
 */
#define UIP_RTO         3

/**
 * The maximum number of times a segment should be retransmitted
 * before the connection should be aborted.一段数据最大重传多少次才取消连接
 *
 * This should not be changed.
 */
#define UIP_MAXRTX      8

/**
 * The maximum number of times a SYN segment should be retransmitted
 * before a connection request should be deemed to have been
 * unsuccessful.一段SYN数据最大重传多少次才认定连接请求失败
 *
 * This should not need to be changed.
 */
#define UIP_MAXSYNRTX      5

/**
 * The TCP maximum segment size.
 * TCP段最大大小
 * This is should not be to set to more than
 * UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN. 不要设置超过这个大小的值 
 */
#define UIP_TCP_MSS     (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)

/**
 * The size of the advertised receiver's window.
 * 接收窗口的大小
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
 * 多久的连接听该停留在TIME_WAIT状态
 * This configiration option has no real implication, and it should be
 * left untouched.这个选项没有实际意义，应当保持不变
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
 * ARP表的大小
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
 * uip数据包缓存区的大小
 * The uIP packet buffer should not be smaller than 60 bytes, and does
 * not need to be larger than 1500 bytes. Lower size results in lower
 * TCP throughput, larger size results in higher TCP throughput.
 * uip数据包缓存区大小应当不小于60字节，不大于1500字节，缓冲区越大TCP的吞吐量越高
 * \hideinitializer
 */
#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_BUFSIZE     1520	/*原始uip为400*/
#else /* UIP_CONF_BUFFER_SIZE */
#define UIP_BUFSIZE UIP_CONF_BUFFER_SIZE
#endif /* UIP_CONF_BUFFER_SIZE */


/**
 * Determines if statistics support should be compiled in. 是否支持编译统统计功能
 *
 * The statistics is useful for debugging and to show the user. 统计功能对于调试非常有用
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_STATISTICS
#define UIP_STATISTICS  1
#else /* UIP_CONF_STATISTICS */
#define UIP_STATISTICS UIP_CONF_STATISTICS
#endif /* UIP_CONF_STATISTICS */

/**
 * Determines if logging of certain events should be compiled in. 确定某些事件的日志功能是否编译
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
 * Broadcast support. 广播功能是否支持
 *
 * This flag configures IP broadcast support. This is useful only
 * together with UDP. 这个标识配置ip广播功能是否支持，仅对UDP起作用
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
 * Print out a uIP log message.	打印日志信息
 *
 * This function must be implemented by the module that uses uIP, and
 * is called by uIP whenever a log message is generated. 
 * 必须实现这个模块，该功能才能使用
 */
void uip_log(char *msg);

/**
 * The link level header length.
 * 链路层头的长度
 * This is the offset into the uip_buf where the IP header can be
 * found. For Ethernet, this should be set to 14. For SLIP, this
 * should be set to 0.
 * 这是一个uip_buf的偏移量，用来找到IP数据包的报头。通常应当设置为14，对于滑移来说这个值应当被设置为0
 * \hideinitializer
 */
 /*IP包在整个以太网帧中的起始地址*/
#ifdef UIP_CONF_LLH_LEN
#define UIP_LLH_LEN UIP_CONF_LLH_LEN
#else /* UIP_CONF_LLH_LEN */
#define UIP_LLH_LEN     14	/*以太网帧头共14字节*/
#endif /* UIP_CONF_LLH_LEN */

/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \name CPU architecture configuration CPU架构配置
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
#ifdef UIP_CONF_BYTE_ORDER	//确定cpu是使用大端模式还是小端模式
#define UIP_BYTE_ORDER     UIP_CONF_BYTE_ORDER
#else /* UIP_CONF_BYTE_ORDER */
#define UIP_BYTE_ORDER     UIP_LITTLE_ENDIAN
#endif /* UIP_CONF_BYTE_ORDER */

/** @} */
/*------------------------------------------------------------------------------*/

/**
 * \name Appication specific configurations 应用程序具体配置
 * @{
 *
 * An uIP application is implemented using a single application
 * function that is called by uIP whenever a TCP/IP event occurs. The
 * name of this function must be registered with uIP at compile time
 * using the UIP_APPCALL definition.
 * 实现一个简单的uip应用程序，当发生TCP/IP事件时通过uip协议调用它。
 * 这个函数的名字在编译时必须要以APPCALL标签定义
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
