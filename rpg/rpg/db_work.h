/*!
 * \file db_work.h
 *
 * \author ziquan
 * \date 四月 2019
 *
 * \brief 数据库多线程
 */
#ifndef _db_work_
#define _db_work_
#include <queue>
#include <map>
#include <thread>
#include <mutex>
#include <ctime>
#include <iostream>
#include "db.h"
#include "singleton.h"

class DBWork;
typedef std::function<void(DBWork*)> TASK_FUN;


class DBWork
{
public:
	DBWork(int thread_num = 2);
	~DBWork();
	void add_task(TASK_FUN);
	void run();
	mutex& get_lock();
	bool is_task_empty();
	queue<TASK_FUN>& get_task_queue();
	DataBase* get_database(char* db_name);
private:
	int thread_n;
	bool is_deatch;
	mutex lock;
	queue<TASK_FUN> work_queue;					// 任务队列
	map<std::thread::id, std::thread*> work_thread;	// 工作线程
	map<string, DataBase*> work_mysql;
};
#endif