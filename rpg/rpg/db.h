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
#include <mutex>
using namespace std;


#define DATA_RESULT	MYSQL_RES*
#define GET_RESULT_ROW mysql_fetch_row


class DataBase
{
public:
	DataBase(char* host, int port, char* user, char* pwd);
	DataBase(char* host, int port, char* user, char* pwd, char* db_name);
	~DataBase();
	void connect(char* db_name);
	void execute(char* sql);
	void execute(char* sql, int& col_n, DATA_RESULT& result);
	void close();
protected:
private:
	char* host;
	int port;
	char* user;
	char* pwd;
	char* db_name;
	mutex lock;
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
};




#endif
