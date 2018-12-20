/*!
 * \file buff.h
 *
 * \author ziquan
 * \date ʮһ�� 2018
 *
 * \brief ����㻺��
 */
#include <boost/asio.hpp>
#define BUFF_HEAD_SIZE 4
#define BUFF_BODY_SIZE 1024 //msg body���1024b


class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + BUFF_BODY_SIZE];


	Buff(){}
	~Buff() {}

	int size(){ return BUFF_HEAD_SIZE + BUFF_BODY_SIZE; }
	char* data(){ return this->m_char; }
};
