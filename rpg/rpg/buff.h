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

#include <boost/asio.hpp>
#include <stdlib.h>
#include <stdio.h> 
#define BUFF_HEAD_SIZE 4
#define BUFF_BODY_SIZE 512


class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + BUFF_BODY_SIZE];
	int recv_length; // 表示本次收到的消息体长度

	Buff(){}
	~Buff() {}

	int size()
	{
		return BUFF_HEAD_SIZE + BUFF_BODY_SIZE;
	}

	char* data()
	{
		return this->m_char;
	}


	bool decode_header()
	{
		char header[BUFF_HEAD_SIZE + 1] = "";
		std::strncat(header, m_char, BUFF_HEAD_SIZE);
		this->recv_length = std::atoi(header);
		std::cout << "recv msg head: " << this->recv_length << std::endl;
		if (this->recv_length > BUFF_BODY_SIZE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	char* head()
	{
		return m_char;
	}

	char* body()
	{
		return m_char + BUFF_HEAD_SIZE;
	}

	void reset()
	{
		
	}
};

#endif