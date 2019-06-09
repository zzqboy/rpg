/*!
 * \file login
 *
 * \author ziquan
 * \date 2019/02/24
 *
 * \brief  µÇÂ¼Ä£¿é
 */
#ifndef _login_
#define _login_
#include "login_proto.h"
#include "db_work.h"

class Login
{
public:
	static void OnLogin(const char* msg);
	static void _lookup_role_fun(DBWork* db_work, string name, string pass);
private:
};



#endif