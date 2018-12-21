/*!
 * \file counter.h
 *
 * \author ziquan
 * \date 十二月 2018
 *
 * \brief 计数器
 */
#ifndef _counter_
#define _counter_


#include "singleton.h"

// 单调递增的计数器
class Counter:public Singleton<Counter>
{
private:
	int last_num = 0;
public:
	Counter(){};
	~Counter(){};

	int get_count()
	{
		int now = last_num;
		last_num += 1;
		return now;
	}
};

#endif