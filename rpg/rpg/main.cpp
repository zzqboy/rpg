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
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "counter.h"
#include "network.h"
using namespace std;

typedef boost::shared_ptr<Network> _NetWorkPtr;

int main(int argc, char* argv[])
{
	try
	{
		Counter::New();
		boost::asio::io_service io_service;

		_NetWorkPtr my_network(new Network(8888, io_service));
		my_network->listen();
		io_service.run();

		std::cout << "end...." << std::endl;
		cin.get();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}