#include "db_work.h"


void do_task(DBWork* db_work)
{
	while (true)
	{
		TASK_FUN fun;

		db_work->get_lock().lock();
		if (!db_work->is_task_empty())
		{
			fun = db_work->get_task_queue().front();
			db_work->get_task_queue().pop();
		}
		db_work->get_lock().unlock();
		
		if (fun)
		{
			fun(db_work);
		}
	}
}


DBWork::DBWork(int thread_n)
{
	DataBase* role_db = new DataBase("127.0.0.1", 3306, "root", "root", "rpg");
	this->work_mysql["rpg"] = role_db;
	this->thread_n = thread_n;
}

DBWork::~DBWork()
{
	for (auto it = this->work_mysql.begin(); it != this->work_mysql.end();++it)
	{
		DataBase* db = it->second;
		db->close();
		delete db;
	}
	this->work_mysql.clear();

	for (auto it = this->work_thread.begin(); it != this->work_thread.end();++it)
	{
		delete it->second;
	}
}

void DBWork::add_task(TASK_FUN task_fun)
{
	this->get_lock().lock();
	this->work_queue.push(task_fun);
	this->get_lock().unlock();
}

mutex& DBWork::get_lock()
{
	return this->lock;
}

bool DBWork::is_task_empty()
{
	return this->work_queue.empty();
}

void DBWork::run()
{
	// 初始化线程
	printf("star run dbwork thread %i\n", this->thread_n);
	for (int n = 0; n < this->thread_n; ++n)
	{	
		thread* t = new thread(do_task, this);
		t->detach();
		this->work_thread[t->get_id()] = t;
	}
}

queue<TASK_FUN>& DBWork::get_task_queue()
{
	return this->work_queue;
}

DataBase* DBWork::get_database(char* db_name)
{
	auto it = this->work_mysql.find(db_name);
	if (it != this->work_mysql.end())
	{
		return it->second;
	}
	return NULL;
}