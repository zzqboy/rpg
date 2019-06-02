/*!
 * \file test_db.h
 *
 * \author ziquan
 * \date 三月 2019
 *
 * \brief 测试数据库
 */
#ifndef _test_db_
#define _test_db_

#include <iostream>
#include <chrono>
#include <Windows.h>
#include "db.h"
#include "db_work.h"


class test_db
{
public:
	test_db();
	~test_db();


	static void task_fun(DBWork*);
	void run_select(bool is_thread, int count);

	void test();
	void test2();
	void test3();
	void test4();
private:
	DataBase* db;
	DBWork* db_work;
	static int count;
};

#endif // !_test_db_

