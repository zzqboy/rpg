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
#define BUFF_HEAD_SIZE 4 // ��Ϣͷ ������Ϣ������ֽ���
#define BUFF_BODY_SIZE 1024 //msg body���1024b


class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + BUFF_BODY_SIZE];
	int recv_length; // ��ʾ�����յ�����Ϣ�峤��

	Buff(){}
	~Buff() {}

	int size(){ return BUFF_HEAD_SIZE + BUFF_BODY_SIZE; }
	char* data(){ return this->m_char; }

	bool decode_header() // �ж���Ϣͷ�Ƿ�Ϸ�
	{
		char header[BUFF_HEAD_SIZE + 1] = "";
		std::strncat(header, m_char, BUFF_HEAD_SIZE);
		int h_l = std::atoi(header);
		if (h_l > BUFF_BODY_SIZE)
		{
			printf("��Ϣͷ�ĳ��ȹ���");
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