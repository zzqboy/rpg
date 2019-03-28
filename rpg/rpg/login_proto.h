/*!
 * \file login_proto.h
 *
 * \author ziquan
 * \date 二月 2019
 *
 * \brief 登录结构体
 */
#ifndef _login_proto_
#define _login_proto_
#pragma pack(1)

namespace Proto
{
	struct Login
	{
		char name[20];
		char password[20];
	};
}

#pragma pack()
#endif