#include "ringbuff.h"
#include <malloc.h>

RingBuff::RingBuff()
{
	this->data = (char*)malloc(MAX_BUFF_SIZE * sizeof(char));
	this->read_pos = this->write_pos = 0;
	this->tol_size = MAX_BUFF_SIZE;
}


RingBuff::~RingBuff()
{
	free(this->data);
	this->data = NULL;
}


void RingBuff::write(char* write_byte, int size)
{
	if (this->GetEmptySize() - 1 < size)
	{
		int re_size = this->tol_size * 2;
		this->resize(re_size);
		this->write(write_byte, size);
		return;
	}
	if ((this->tol_size - this->write_pos) >= size)
	{
		memcpy(this->data + this->write_pos, write_byte, size);
	}
	else
	{
		int tail_size = this->tol_size - this->write_pos;
		memcpy(this->data + this->write_pos, write_byte, tail_size);
		memcpy(this->data, write_byte + tail_size, size - tail_size);
	}
}


bool RingBuff::read(char* read_byte, int size)
{
	int can_size = this->GetReadableSize();
	if (can_size < size)
	{
		return false;
	}
	if (this->write_pos > this->read_pos)
	{
		memcpy(read_byte, this->data+ this->read_pos, size);
		this->read_pos += size;
	}
	else
	{
		if ((this->tol_size - this->read_pos) >= size)
		{
			memcpy(read_byte, this->data+this->read_pos, size);
			this->read_pos += size;
		}
		else
		{
			int tail_size = this->tol_size - this->read_pos;
			memcpy(read_byte, this->data+this->read_pos, tail_size);
			memcpy(read_byte + tail_size, this->data, size - tail_size);
			this->read_pos = size - tail_size;
		}
	}
	if (this->read_pos == this->write_pos)
	{
		this->reset();
	}
	return true;
}


void RingBuff::reset()
{
	this->read_pos = 0;
	this->write_pos = 0;
}


bool RingBuff::resize(int size)
{
	if (size <= this->tol_size)
	{
		return false;
	}
	int write_size = this->GetReadableSize();
	char* new_data = (char*)malloc(size * sizeof(char));
	if (this->read(new_data, write_size))
	{
		free(this->data);
		this->data = new_data;
		this->read_pos = 0;
		this->write_pos = write_size;
		this->tol_size = size;
		return true;
	}
	else
	{
		return false;
	}
}


bool RingBuff::CanWriteSize(int size)
{
	if (this->GetEmptySize() >= size)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int RingBuff::GetEmptySize()
{
	if (this->write_pos > this->read_pos)
	{
		return this->read_pos + this->tol_size - this->write_pos;
	}
	if (this->read_pos > this->write_pos)
	{
		return this->read_pos - this->write_pos;
	}
	if (read_pos == 0)
	{
		return this->tol_size;
	}
	else
	{
		return 0;
	}
}

int RingBuff::GetReadableSize()
{
	return this->tol_size - this->GetEmptySize();
}

char* RingBuff::GetBuff()
{
	return this->data;
}

int RingBuff::GetReadPos()
{
	return this->read_pos;
}

int RingBuff::GetWritePos()
{
	return this->write_pos;
}