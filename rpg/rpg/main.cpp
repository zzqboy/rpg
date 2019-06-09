/*!
 * \file main.cpp
 *
 * \author ziquan
 * \date 十二月 2018
 *
 * \brief 总入口
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
		// 初始化
		Server::New();
		// 开始循环
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