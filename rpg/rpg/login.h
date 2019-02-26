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

class Login
{
public:
	static void CreateRole(const char* msg);
	void InitRole(const char* msg);
	static void Start();
private:
};

void Login::CreateRole(const char* msg)
{
	Proto::Login* login_s = (Proto::Login*)msg;
	printf("create role %s %s", login_s->name, login_s->password);
}



#endif