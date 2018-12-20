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

#include "test_counter.h"
#include "test_network.h"

int main(int argc, char* argv[])
{
	test_network();
}