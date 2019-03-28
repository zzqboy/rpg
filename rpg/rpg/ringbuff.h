/*!
* \file buff.h
*
* \author ziquan
* \date ʮһ�� 2018
*
* \brief ����㻺�壬���ڷ���
*/
#ifndef _ring_buff_
#define _ring_buff_

#include <stdio.h> 
#include <iostream>
#define MAX_BUFF_SIZE 1024  // ��ʼ����

// ���λ��棬���ڷ���
class RingBuff
{
private:
	char *data;
	int read_pos;
	int write_pos;
	int tol_size;

public:
	RingBuff();
	~RingBuff();
	// ��д
	void write(char* write_byte, int size);
	bool read(char* read_data, int size);
	void reset();
	bool resize(int size);
	// �ж�
	bool CanWriteSize(int size);
	int GetEmptySize();
	int GetReadableSize();
	char* GetBuff();
	int GetReadPos();
	int GetWritePos();
};

#endif