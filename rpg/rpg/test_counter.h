/*!
 * \file test_counter.h
 *
 * \author ziquan
 * \date 十二月 2018
 *
 * \brief 测试计数器
 */
#include "counter.h"
#include <stdio.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

boost::mutex io_mutex;

struct use_count
{
	use_count(int id) : id(id) { }

	void operator()()
	{
		for (int i = 0; i < 100; ++i)
		{
			boost::mutex::scoped_lock lock(io_mutex);
			Counter* c = Counter::GetInstance();
			printf("now id %i count %p --> %i \n", id, c, c->get_count());
		}
	}
	int id;
};


void test()
{
	Counter::New();
	boost::thread t1(use_count(1));
	boost::thread t2(use_count(2));
	t1.join();
	t2.join();
}
