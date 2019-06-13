#include "login.h"
#include <iostream>
#include "tool.h"
using namespace std;


void Login::OnLogin(const char* msg)
{
	Proto::Login* login_s = (Proto::Login*)msg;
	string name = login_s->name;
	string pass = login_s->password;
}