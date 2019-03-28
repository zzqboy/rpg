#include "test_db.h"

void test_db::test()
{
	DataBase db("127.0.0.1", 3306, "root", "root");
	db.connect("test");
	db.execute("select * from role;");
}