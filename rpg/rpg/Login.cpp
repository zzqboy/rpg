#include "login.h"
#include <iostream>
#include "tool.h"
using namespace std;


void Login::OnLogin(const char* msg)
{
	Proto::Login* login_s = (Proto::Login*)msg;
	string name = login_s->name;
	string pass = login_s->password;
	auto fun = std::bind(_lookup_role_fun, placeholders::_1, name, pass);
	DBWork::GetInstance()->add_task(fun);
}

void Login::_lookup_role_fun(DBWork* db_work, string name, string pass)
{
	char* cmd = "select * from role where role_name = %s and role_key = %s;";
	char cmd_buff[512];
	sprintf(cmd_buff, cmd, name.c_str(), pass.c_str());

	DataBase* db = db_work->get_database("rpg");
	int col_n = 0;
	char** row;
	DATA_RESULT result = NULL;
	db->execute(cmd_buff, col_n, result);
	int role_id = -1;
	while (row = GET_RESULT_ROW(result))
	{
		role_id = *(int*)row[0];
	}
}