/*!
 * \file main.cpp
 *
 * \author ziquan
 * \date 十二月 2018
 *
 * \brief 总入口
 */
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <stdio.h>
#include "counter.h"

#include "test_counter.h"
#include "test_network.h"

int main(int argc, char* argv[])
{
try
{
	Counter::New();

	Network my_network(8001);
	my_network.listen();
	my_network.run();

}
catch (std::exception& e)
{
	std::cerr << "Exception: " << e.what() << "\n";
}
}