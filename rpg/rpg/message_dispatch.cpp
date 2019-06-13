#include "message_dispatch.h"



void MessageDispatch::Register(int msg_id, fun_ptr fun)
{
	auto iter = this->fun_map.find(msg_id);
	if (iter != this->fun_map.end())
	{
		printf("ע����Ϣ����ʱ�������е�id %i", msg_id);
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
		printf("������Ϣʱû�ҵ�ע�ắ�� %i\n", msg_id);
	}
	else
	{
		auto fun = this->fun_map[msg_id];
		fun(message);
	}
}

void MessageDispatch::InitEvent()
{
	// ��¼Э��
	this->Register(1, Login::OnLogin);
}
