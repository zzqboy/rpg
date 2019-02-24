/*!
 * \file message_dispatch
 *
 * \author ziquan
 * \date 2019/02/24
 *
 * \brief  消息处理模块 分派消息注册函数
 */
#include <map>

// 定义函数指针
typedef void(*fun_ptr)(const char* message);

class MessageDispatch
{
public:
	void Register(int msg_id, fun_ptr fun);
	void Dispatch(int msg_id, const char* message);
protected:
private:
	std::map<unsigned int, fun_ptr> fun_map;
};

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
		printf("处理消息时没找到注册函数 %i", msg_id);
	}
	else
	{
		auto fun = this->fun_map[msg_id];
		fun(message);
	}
}