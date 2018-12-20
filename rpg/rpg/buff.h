/*!
 * \file buff.h
 *
 * \author ziquan
 * \date 十一月 2018
 *
 * \brief 网络层缓冲
 */
#include <boost/asio.hpp>
#define BUFF_HEAD_SIZE 4
#define BUFF_BODY_SIZE 1024 //msg body最大1024b


class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + BUFF_BODY_SIZE];


	Buff(){}
	~Buff() {}

	int size(){ return BUFF_HEAD_SIZE + BUFF_BODY_SIZE; }
	char* data(){ return this->m_char; }
};
