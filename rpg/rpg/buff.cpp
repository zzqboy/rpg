#include "buff.h"

int Buff::size()
{
	return BUFF_HEAD_SIZE + MAX_BUFF_BODY_SIZE;
}


char* Buff::data()
{
	return this->m_char;
}


bool Buff::decode_header()
{
	char header[BUFF_HEAD_SIZE + 1] = "";
	std::strncat(header, m_char, BUFF_HEAD_SIZE);

	this->recv_length = *(int*)header;
	//std::cout << "recv msg head: " << this->recv_length << std::endl;

	if (this->recv_length > MAX_BUFF_BODY_SIZE)
	{
		return false;
	}
	else
	{
		return true;
	}
}


char* Buff::head()
{
	return m_char;
}


char* Buff::body()
{
	return m_char + BUFF_HEAD_SIZE;
}


void Buff::reset()
{
	memset(this->m_char, 0, sizeof(this->m_char));
}