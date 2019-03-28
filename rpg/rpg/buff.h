/*!
 * \file buff.h
 *
 * \author ziquan
 * \date 十一月 2018
 *
 * \brief 网络层缓冲
 */
#ifndef _buff_
#define _buff_

#include <stdio.h> 
#include <iostream>
#define BUFF_HEAD_SIZE 4  // 先接收一个4个字节的整数头，表示消息体的长度
#define MAX_BUFF_BODY_SIZE 1024  // 一个消息体的最大长度


// 接收消息体
class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + MAX_BUFF_BODY_SIZE];
	int recv_length; // 表示本次收到的消息体长度

	int size();
	char* data();
	bool decode_header();
	char* head();
	char* body();
	void reset();
};

#endif