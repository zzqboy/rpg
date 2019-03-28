/*!
 * \file db.h
 *
 * \author ziquan
 * \date 三月 2019
 *
 * \brief 数据库
 */
#ifndef _db_
#define _db_
#include <Windows.h>
#include <mysql.h>
#include <stdio.h>
using namespace std;

class DataBase
{
public:
	DataBase(char* host, int port, char* user, char* pwd);
	~DataBase();
	void connect(char* db_name);
	void execute(char* sql);
	void close();
protected:
private:
	char* host;
	int port;
	char* user;
	char* pwd;
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
};




#endif
