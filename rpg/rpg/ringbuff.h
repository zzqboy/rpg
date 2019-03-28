/*!
* \file buff.h
*
* \author ziquan
* \date 十一月 2018
*
* \brief 网络层缓冲，用于发送
*/
#ifndef _ring_buff_
#define _ring_buff_

#include <stdio.h> 
#include <iostream>
#define MAX_BUFF_SIZE 1024  // 起始长度

// 环形缓存，用于发送
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
	// 读写
	void write(char* write_byte, int size);
	bool read(char* read_data, int size);
	void reset();
	bool resize(int size);
	// 判断
	bool CanWriteSize(int size);
	int GetEmptySize();
	int GetReadableSize();
	char* GetBuff();
	int GetReadPos();
	int GetWritePos();
};

#endif