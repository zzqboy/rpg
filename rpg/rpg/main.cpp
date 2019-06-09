/*!
 * \file main.cpp
 *
 * \author ziquan
 * \date ʮ���� 2018
 *
 * \brief �����
 */
#include <iostream>
#include <stdio.h>

#include "server.h"
#include "test_db.h"
using namespace std;


int main(int argc, char* argv[])
{
	try
	{
		// ��ʼ��
		Server::New();
		// ��ʼѭ��
		Server::GetInstance()->run();
		std::cout << "finish init server...." << std::endl;

		cin.get();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}