/*!
 * \file buff.h
 *
 * \author ziquan
 * \date ʮһ�� 2018
 *
 * \brief ����㻺��
 */
#ifndef _buff_
#define _buff_

#include <boost/asio.hpp>
#include <stdlib.h>
#include <stdio.h> 
#define BUFF_HEAD_SIZE 4  // �Ƚ���һ��4���ֽڵ�����ͷ����ʾ��Ϣ��ĳ���
#define MAX_BUFF_BODY_SIZE 1024  // һ����Ϣ�����󳤶�


class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + MAX_BUFF_BODY_SIZE];
	int recv_length; // ��ʾ�����յ�����Ϣ�峤��

	Buff(){}
	~Buff() {}

	int size()
	{
		return BUFF_HEAD_SIZE + MAX_BUFF_BODY_SIZE;
	}

	char* data()
	{
		return this->m_char;
	}


	bool decode_header()
	{
		char header[BUFF_HEAD_SIZE + 1] = "";
		std::strncat(header, m_char, BUFF_HEAD_SIZE);

		this->recv_length = *(int*)header;
		std::cout << "recv msg head: " << this->recv_length << std::endl;

		if (this->recv_length > MAX_BUFF_BODY_SIZE)
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
		memset(this->m_char, 0, sizeof(this->m_char));
	}
};

#endif