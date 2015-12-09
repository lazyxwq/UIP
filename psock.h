/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
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
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: psock.h,v 1.3 2006/06/12 08:00:30 adam Exp $
 */

/**
 * \defgroup psock Protosockets library
 * @{
 *
 * The protosocket library provides an interface to the uIP stack that is
 * similar to the traditional BSD socket interface. Unlike programs
 * written for the ordinary uIP event-driven interface, programs
 * written with the protosocket library are executed in a sequential
 * fashion and does not have to be implemented as explicit state
 * machines.
 	原始套接字库文件为UIP协议栈提供了一个与传统BSD套接字类似的接口。
 	不同于为普通的UIP时间驱动接口写的程序，为原始套接字写接口写的程序是顺序执行的，
 	并且不需要实现复炸的状态机。
 *
 * Protosockets only work with TCP connections.
 	原始套接字只能用于TCP连接。
 *
 * The protosocket library uses \ref pt protothreads to provide
 * sequential control flow. This makes the protosockets lightweight in
 * terms of memory, but also means that protosockets inherits the
 * functional limitations of protothreads. Each protosocket lives only
 * within a single function. Automatic variables (stack variables) are
 * not retained across a protosocket library function call.
 	原始套接字库使用原始线程来提供顺序控制流。
 	这使得原始套接字在内存方面变得轻量级，但同时也意味着，
 	原始套接字继承了原始线程的一些限制。比如原始套接字只能
 	生存与单个函数中。自动变量(栈变量)的值不能跨原始套接字函数保留。
 *
 * \note Because the protosocket library uses protothreads, local
 * variables will not always be saved across a call to a protosocket
 * library function. It is therefore advised that local variables are
 * used with extreme care.
 	应为原始套接字使用了原始线程，局部变量并不总能得到保存。
 	因此所以这里建议局部变量的使用需要小心。
 *
 * The protosocket library provides functions for sending data without
 * having to deal with retransmissions and acknowledgements, as well
 * as functions for reading data without having to deal with data
 * being split across more than one TCP segment.
 	原始套接字库提供了一些无需处理重传和回应的发送数据的函数。
 	和一些无需对被分解成多个TCP段的数据进行处理的读取数据的函数。
 *
 * Because each protosocket runs as a protothread, the protosocket has to be
 * started with a call to PSOCK_BEGIN() at the start of the function
 * in which the protosocket is used. Similarly, the protosocket protothread can
 * be terminated by a call to PSOCK_EXIT().
 	因为么个原始套接字都作为一个原始线程来运行，所以应在
 	原始套接字的函数起始调用PSOCK_BEGIN()来启动原始套接字。
 	类似的，原始套接字可以通过调用PSOCK_EXIT()函数终止。
 *
 */

/**
 * \file
 * Protosocket library header file
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __PSOCK_H__
#define __PSOCK_H__

#include "uipopt.h"
#include "pt.h"

 /*
 * The structure that holds the state of a buffer.
 	这个结构体保存了缓冲区的状态
 *
 * This structure holds the state of a uIP buffer. The structure has
 * no user-visible elements, but is used through the functions
 * provided by the library.
 	这个结构体保存了UIP缓冲区的状态，
 	该结构体是对用户不可见的元素。
 	但是通过库文件提供了函数使用它。
 *
 */
struct psock_buf {
  u8_t *ptr;
  unsigned short left;
};

/**
 * The representation of a protosocket.	代表了一个原始套接字
 *
 * The protosocket structrure is an opaque structure with no user-visible
 * elements.
 	这个原始套接字结构是一个对用户不透明的结构体。
 */
struct psock {
  struct pt pt, psockpt; /* Protothreads - one that's using the psock
			    functions, and one that runs inside the
			    psock functions. 原始线程，一个使用PSOCK函数并运行在怕sock函数上*/
  const u8_t *sendptr;   /* Pointer to the next data to be sent. 指向下一个需要发送的数据*/
  u8_t *readptr;         /* Pointer to the next data to be read. 指向下一个需要读取的数据*/
  
  char *bufptr;          /* Pointer to the buffer used for buffering
			    incoming data. 指向传入缓冲区的数据的指针*/
  
  u16_t sendlen;         /* The number of bytes left to be sent. 需要发送的字节数*/
  u16_t readlen;         /* The number of bytes left to be read. 需要读取的字节数*/

  struct psock_buf buf;  /* The structure holding the state of the
			    input buffer. 保存了输入缓冲区的状态*/
  unsigned int bufsize;  /* The size of the input buffer. 输入缓冲区的大小*/
  
  unsigned char state;   /* The state of the protosocket. 原始套接字的状态*/
};

void psock_init(struct psock *psock, char *buffer, unsigned int buffersize);
/**
 * Initialize a protosocket. 初始化一个原始套接字
 *
 * This macro initializes a protosocket and must be called before the
 * protosocket is used. The initialization also specifies the input buffer
 * for the protosocket.
 	这个宏初始化一个原始套接字并且要在该原始套接字被使用之前调用。
 	初始化还制定了用于原始套接字的输入缓冲区。
 *
 * \param psock (struct psock *) A pointer to the protosocket to be
 * initialized 参数psock指向一个需要初始化的套接字
 *
 * \param buffer (char *) A pointer to the input buffer for the
 * protosocket. 参数buffer指向一个用于套接字的输入缓冲区
 *
 * \param buffersize (unsigned int) The size of the input buffer. 参数buffersize是输入缓冲区的大小
 *
 * \hideinitializer
 */
#define PSOCK_INIT(psock, buffer, buffersize) \
  psock_init(psock, buffer, buffersize)

/**
 * Start the protosocket protothread in a function. 在函数中启用一个原始套接字
 *
 * This macro starts the protothread associated with the protosocket and
 * must come before other protosocket calls in the function it is used.
 	在函数中使用其他的原始套接字之前必须先使用这个宏
 *
 * \param psock (struct psock *) A pointer to the protosocket to be
 * started.参数psock指向需要启动的原始套接字
 *
 * \hideinitializer
 */
#define PSOCK_BEGIN(psock) PT_BEGIN(&((psock)->pt))	/*在函数中启用一个原始套接字*/

PT_THREAD(psock_send(struct psock *psock, const char *buf, unsigned int len));
/**
 * Send data.	发送数据
 *
 * This macro sends data over a protosocket. The protosocket protothread blocks
 * until all data has been sent and is known to have been received by
 * the remote end of the TCP connection.
 	这个宏可以在原始套接字中发送数据。原始套接字
 	会等到发送完所有的数据并由已知的TCP连接的远程端接收。
 	
 *
 * \param psock (struct psock *) A pointer to the protosocket over which
 * data is to be sent.参数指向需要发送的原始套接字
 *
 * \param data (char *) A pointer to the data that is to be sent. 参数指向需要发送的数据
 *
 * \param datalen (unsigned int) The length of the data that is to be
 * sent.参数是需要发送的数据的大小
 *
 * \hideinitializer
 */
#define PSOCK_SEND(psock, data, datalen)		\
    PT_WAIT_THREAD(&((psock)->pt), psock_send(psock, data, datalen))

/**
 * \brief      Send a null-terminated string.发送一个以零结尾的字符串
 * \param psock Pointer to the protosocket.参数指向套接字
 * \param str  The string to be sent.参数指向发送的字符串
 *
 *             This function sends a null-terminated string over the
 *             protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_SEND_STR(psock, str)      		\
    PT_WAIT_THREAD(&((psock)->pt), psock_send(psock, str, strlen(str)))

PT_THREAD(psock_generator_send(struct psock *psock,
				unsigned short (*f)(void *), void *arg));

/**
 * \brief      Generate data with a function and send it 生成数据并发送
 * \param psock Pointer to the protosocket.指向套接字
 * \param generator Pointer to the generator function指向生成数据的函数的指针
 * \param arg   Argument to the generator function 要传给函数的参数
 *
 *             This function generates data and sends it over the
 *             protosocket. This can be used to dynamically generate
 *             data for a transmission, instead of generating the data
 *             in a buffer beforehand. This function reduces the need for
 *             buffer memory. The generator function is implemented by
 *             the application, and a pointer to the function is given
 *             as an argument with the call to PSOCK_GENERATOR_SEND().
 	此宏用于通过函数残生数据，并通过原始套接字发送。他可以动态产生数据并传输。
 	较小了缓冲区的开销。而不必事先将内容写入缓冲区。产生器函数由应用函数实现，
 	使用时要将函数的指针作为一个参数传给宏。
 *
 *             The generator function should place the generated data
 *             directly in the uip_appdata buffer, and return the
 *             length of the generated data. The generator function is
 *             called by the protosocket layer when the data first is
 *             sent, and once for every retransmission that is needed.
 	生成器函数应当将产生的数据直接放入uip_appdata_buff中，返回产生的数据的长度。
 	数据每一次发送时，原始套接字层会调用产生器函数，并且如果出现重发的情况，
 	也会调用一次该函数，因此重发的数据并不是上次的数据。
 	
 *
 * \hideinitializer
 */
#define PSOCK_GENERATOR_SEND(psock, generator, arg)     \
    PT_WAIT_THREAD(&((psock)->pt),					\
		   psock_generator_send(psock, generator, arg))


/**
 * Close a protosocket. 关闭套接字
 *
 * This macro closes a protosocket and can only be called from within the
 * protothread in which the protosocket lives.
 	只能用于原始套接字生存的原始线程中
 *
 * \param psock (struct psock *) A pointer to the protosocket that is to
 * be closed.
 *
 * \hideinitializer
 */
#define PSOCK_CLOSE(psock) uip_close()

PT_THREAD(psock_readbuf(struct psock *psock));
/**
 * Read data until the buffer is full. 读数据知道缓冲区满
 *
 * This macro will block waiting for data and read the data into the
 * input buffer specified with the call to PSOCK_INIT(). Data is read
 * until the buffer is full..
 	此宏会阻塞等待数据读入到由PSOCK_INIT()指定的输入缓冲区，
 	读数据操作会进行到缓冲区满
 *
 * \param psock (struct psock *) A pointer to the protosocket from which
 * data should be read.指向读取数据来源套接字的指针
 *
 * \hideinitializer
 */
#define PSOCK_READBUF(psock)				\
  PT_WAIT_THREAD(&((psock)->pt), psock_readbuf(psock))

PT_THREAD(psock_readto(struct psock *psock, unsigned char c));
/**
 * Read data up to a specified character.读取数据直到一个固定的字符出现	
 *
 * This macro will block waiting for data and read the data into the
 * input buffer specified with the call to PSOCK_INIT(). Data is only
 * read until the specifieed character appears in the data stream.
 	此宏会阻塞等待并开始读取数据到由PSOCK_INIT()指定的输入缓冲区中，
 	数据读取会一直持续知道某个固定的字符出现为止
 	
 *
 * \param psock (struct psock *) A pointer to the protosocket from which
 * data should be read.
 *
 * \param c (char) The character at which to stop reading.
 *
 * \hideinitializer
 */
#define PSOCK_READTO(psock, c)				\
  PT_WAIT_THREAD(&((psock)->pt), psock_readto(psock, c))

/**
 * The length of the data that was previously read.返回之前读到的数据的长度
 *
 * This macro returns the length of the data that was previously read
 * using PSOCK_READTO() or PSOCK_READ().
 	返回之前由PSOCK_READTO()或PSOCK_READ()函数读到的数据的长度
 *
 * \param psock (struct psock *) A pointer to the protosocket holding the data.
 *
 * \hideinitializer
 */
#define PSOCK_DATALEN(psock) psock_datalen(psock)

u16_t psock_datalen(struct psock *psock);

/**
 * Exit the protosocket's protothread.终止原始套接字的原始线程
 *
 * This macro terminates the protothread of the protosocket and should
 * almost always be used in conjunction with PSOCK_CLOSE().
 	此宏用于终止原始套接字的原始线程，必须与PSOCK_CLOSE()一起使用。
 *
 * \sa PSOCK_CLOSE_EXIT()
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_EXIT(psock) PT_EXIT(&((psock)->pt))

/**
 * Close a protosocket and exit the protosocket's protothread.关闭一个套接字并推出原始套接字生存的线程
 *
 * This macro closes a protosocket and exits the protosocket's protothread.
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_CLOSE_EXIT(psock)		\
  do {						\
    PSOCK_CLOSE(psock);			\
    PSOCK_EXIT(psock);			\
  } while(0)

/**
 * Declare the end of a protosocket's protothread.声明原始套接字的原始线程的结束
 *
 * This macro is used for declaring that the protosocket's protothread
 * ends. It must always be used together with a matching PSOCK_BEGIN()
 * macro.常喝PSOCK_BEGIN()配合使用
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_END(psock) PT_END(&((psock)->pt))

char psock_newdata(struct psock *s);

/**
 * Check if new data has arrived on a protosocket.检查是否有数据到达套接字
 *
 * This macro is used in conjunction with the PSOCK_WAIT_UNTIL()
 * macro to check if data has arrived on a protosocket.
 	配合PSOCK_WAIT_UNTIL()函数使用，查看套接字上是否有新的数据到达
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 *
 * \hideinitializer
 */
#define PSOCK_NEWDATA(psock) psock_newdata(psock)

/**
 * Wait until a condition is true.阻塞直到条件为真
 *
 * This macro blocks the protothread until the specified condition is
 * true. The macro PSOCK_NEWDATA() can be used to check if new data
 * arrives when the protosocket is waiting.
 	宏PSOCK_NEWDATA()可以用来检查此宏在阻塞期间是否有数据到达。
 *
 * Typically, this macro is used as follows:
 *
 \code
 PT_THREAD(thread(struct psock *s, struct timer *t))
 {
   PSOCK_BEGIN(s);

   PSOCK_WAIT_UNTIL(s, PSOCK_NEWADATA(s) || timer_expired(t));
   
   if(PSOCK_NEWDATA(s)) {
     PSOCK_READTO(s, '\n');
   } else {
     handle_timed_out(s);
   }
   
   PSOCK_END(s);
 }
 \endcode
 *
 * \param psock (struct psock *) A pointer to the protosocket.
 * \param condition The condition to wait for.
 *
 * \hideinitializer
 */
#define PSOCK_WAIT_UNTIL(psock, condition)    \
  PT_WAIT_UNTIL(&((psock)->pt), (condition));

#define PSOCK_WAIT_THREAD(psock, condition)   \
  PT_WAIT_THREAD(&((psock)->pt), (condition))

#endif /* __PSOCK_H__ */

/** @} */
