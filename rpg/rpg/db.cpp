#include "db.h"

DataBase::DataBase(char* host, int port, char* user, char* pwd)
{
	mysql_init(&mysql);
	this->host = host;
	this->port = port;
	this->user = user;
	this->pwd = pwd;
	this->result = NULL;
}


DataBase::~DataBase()
{
	this->close();
}


void DataBase::connect(char* db_name)
{
	if (mysql_real_connect(&mysql, host, user, pwd, db_name, 3306, NULL, 0) == NULL)
	{
		printf("fail to connect to database: %s", db_name);
	}
	mysql_query(&this->mysql, "SET NAMES UTF8");
}

void DataBase::execute(char* sql)
{
	int res;
	int col_n;
	res = mysql_query(&this->mysql, sql);
	if (!res)
	{
		result = mysql_store_result(&this->mysql);
		if (result)
		{
			col_n = mysql_num_fields(result);
			while (sql_row = mysql_fetch_row(result))//获取具体的数据
			{
				for (int i = 0; i < col_n; i++)
				{
					printf("%s ", sql_row[i]);
				}
				printf("\n");
			}
		}
	}
	else
	{
		printf("fail to execute:%s", sql);
	}
}

void DataBase::close()
{
	if (this->result)
	{
		mysql_free_result(this->result);
	}
	mysql_close(&this->mysql);
}