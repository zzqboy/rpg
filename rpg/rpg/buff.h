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
#define BUFF_HEAD_SIZE 4 // 消息头 传递消息体最大字节数
#define BUFF_BODY_SIZE 1024 //msg body最大1024b


class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + BUFF_BODY_SIZE];
	int recv_length; // 表示本次收到的消息体长度

	Buff(){}
	~Buff() {}

	int size(){ return BUFF_HEAD_SIZE + BUFF_BODY_SIZE; }
	char* data(){ return this->m_char; }

	bool decode_header() // 判断消息头是否合法
	{
		char header[BUFF_HEAD_SIZE + 1] = "";
		std::strncat(header, m_char, BUFF_HEAD_SIZE);
		int h_l = std::atoi(header);
		if (h_l > BUFF_BODY_SIZE)
		{
			printf("消息头的长度过大");
			return false;
		}
		else
		{
			this->recv_length = h_l;
			return true;
		}
	}

	char* body()
	{
		return m_char + BUFF_HEAD_SIZE;
	}
};

#endif