/*!
 * \file message_dispatch
 *
 * \author ziquan
 * \date 2019/02/24
 *
 * \brief  消息处理模块 分派消息注册函数
 */
#ifndef _message_dispatch_
#define  _message_dispatch_
#include <map>
#include "login.h"


// 定义函数指针
typedef void(*fun_ptr)(const char* message);

class MessageDispatch
{
public:
	void InitEvent();
	void Register(int msg_id, fun_ptr fun);
	void Dispatch(int msg_id, const char* message);
protected:
private:
	std::map<unsigned int, fun_ptr> fun_map;
};
#endif