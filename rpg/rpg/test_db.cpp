#include "test_db.h"


test_db::test_db()
{
	this->db = new DataBase("127.0.0.1", 3306, "root", "root");
	this->db->connect("rpg");
	// 多线程
	this->db_work = new DBWork(12);
}

test_db::~test_db()
{}


void test_db::test(bool is_sleep)
{
	int col_n = 0;
	char** row;
	DATA_RESULT result = NULL;
	this->db->execute("select * from role;", col_n, result);
	while (row = GET_RESULT_ROW(result))
	{
		//printf("%s\n", row[0]);
	}
	if (is_sleep)
	{
		Sleep(10);
	}
}

int test_db::count = 0;

void test_db::task_fun(DBWork* db_work, bool is_sleep)
{
	DataBase* db = db_work->get_database("rpg");
	int col_n = 0;
	char** row;
	DATA_RESULT result = NULL;
	db->execute("select * from role;", col_n, result);
	while (row = GET_RESULT_ROW(result))
	{
		//printf("%s\n", row[0]);
	}
	if (is_sleep)
	{
		Sleep(10);
	}
}

void test_db::test2()
{
	//this->db_work->add_task(test_db::task_fun);
}

void test_db::test3()
{
	//test param
	int count[3] = { 100, 1000, 5000 };
	bool is_sleep = false;

	//multi thread not sleep
	this->db_work->run();
	auto fun = std::bind(test_db::task_fun, placeholders::_1, is_sleep);
	for each(int num in count)
	{
		for (int i = 0; i < num; i++)
		{
			this->db_work->add_task(fun);
		}
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		while (true)
		{
			if (this->db_work->is_task_empty())
			{
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				printf("multi thread\ncount: %i\ntime: %i  microseconds\n\n", num, std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
				break;
			}
		}
	}
	

	// single thread not sleep
	for each (int num in count)
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		for (int i = 0; i < num; i++)
		{
			this->test(is_sleep);
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		printf("single thread\ncount:%i\ntime: %i  microseconds\n\n", num, std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
	}
}

