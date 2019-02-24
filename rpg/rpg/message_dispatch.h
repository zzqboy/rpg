/*!
 * \file message_dispatch
 *
 * \author ziquan
 * \date 2019/02/24
 *
 * \brief  ��Ϣ����ģ�� ������Ϣע�ắ��
 */
#include <map>

// ���庯��ָ��
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
		printf("������Ϣʱû�ҵ�ע�ắ�� %i", msg_id);
	}
	else
	{
		auto fun = this->fun_map[msg_id];
		fun(message);
	}
}