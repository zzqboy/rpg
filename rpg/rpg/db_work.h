/*!
 * \file db_work.h
 *
 * \author ziquan
 * \date ���� 2019
 *
 * \brief ���ݿ���߳�
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
	queue<TASK_FUN> work_queue;					// �������
	map<std::thread::id, std::thread*> work_thread;	// �����߳�
	map<string, DataBase*> work_mysql;
};
#endif