#include "message_dispatch.h"



void MessageDispatch::Register(int msg_id, fun_ptr fun)
{
	auto iter = this->fun_map.find(msg_id);
	if (iter != this->fun_map.end())
	{
		printf("注册消息函数时发现已有的id %i", msg_id);
	}
	else
	{
		this->fun_map[msg_id] = fun;
	}
}

void MessageDispatch::Dispatch(int msg_id, const char* message)
{
	auto iter = this->fun_map.find(msg_id);
	if (iter == this->fun_map.end())
	{
		printf("处理消息时没找到注册函数 %i\n", msg_id);
	}
	else
	{
		auto fun = this->fun_map[msg_id];
		fun(message);
	}
}

void MessageDispatch::InitEvent()
{
	// 登录协议
	this->Register(1, Login::OnLogin);
}
