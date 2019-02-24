/*!
 * \file login
 *
 * \author ziquan
 * \date 2019/02/24
 *
 * \brief  µÇÂ¼Ä£¿é
 */
#ifndef _singleton_
#define _singleton_

struct LoginS
{
	char name[20];
	char password[20];
};

class Login
{
public:
	void CreateRole(const char* msg);
	void InitRole(const char* msg);
	void Start();
private:
};

#endif