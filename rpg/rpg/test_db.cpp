#include "test_db.h"


test_db::test_db()
{
	this->db = new DataBase("127.0.0.1", 3306, "root", "root");
	this->db->connect("rpg");
	// ¶àÏß³Ì
	this->db_work = new DBWork();
}

test_db::~test_db()
{}


void test_db::test()
{
	int col_n = 0;
	char** row;
	DATA_RESULT result = NULL;
	this->db->execute("select * from role;", col_n, result);
	while (row = GET_RESULT_ROW(result))
	{
		//printf("%s\n", row[0]);
	}
	Sleep(1 * 1000);
}

int test_db::count = 0;

void test_db::task_fun(DBWork* db_work)
{
	//printf("thread %i work\n", this_thread::get_id());
	DataBase* db = db_work->get_database("rpg");
	int col_n = 0;
	char** row;
	DATA_RESULT result = NULL;
	db->execute("select * from role;", col_n, result);
	while (row = GET_RESULT_ROW(result))
	{
		//printf("%s\n", row[0]);
	}
	Sleep(1 * 1000);
	//printf("thread %i run task_fun:%i\n", this_thread::get_id(), ++test_db::count);
}

void test_db::test2()
{
	this->db_work->add_task(test_db::task_fun);
}

void test_db::test3()
{
	//multi thread
	int count = 100;
	this->db_work->run();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	for (int i = 0; i < count; i++)
	{
		this->db_work->add_task(test_db::task_fun);
	}
	while (true)
	{
		if (this->db_work->is_task_empty())
		{
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			printf("multi thread time: %i  microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
			break;
		}
	}

	// single thread
	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < count; i++)
	{
		this->test();
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	printf("single thread time: %i  microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
}

