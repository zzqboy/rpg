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
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "server.h"
using namespace std;


int main(int argc, char* argv[])
{
	try
	{
		// ��ʼ��
		Server my_server;
		// ��ʼѭ��
		my_server.run();
		std::cout << "finish init server...." << std::endl;
		cin.get();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}