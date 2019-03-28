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

#include <stdio.h> 
#include <iostream>
#define BUFF_HEAD_SIZE 4  // �Ƚ���һ��4���ֽڵ�����ͷ����ʾ��Ϣ��ĳ���
#define MAX_BUFF_BODY_SIZE 1024  // һ����Ϣ�����󳤶�


// ������Ϣ��
class Buff
{
public:
	char m_char[BUFF_HEAD_SIZE + MAX_BUFF_BODY_SIZE];
	int recv_length; // ��ʾ�����յ�����Ϣ�峤��

	int size();
	char* data();
	bool decode_header();
	char* head();
	char* body();
	void reset();
};

#endif