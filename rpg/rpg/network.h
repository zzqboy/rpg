/*!
* \file Network.h
*
* \author ziquan
* \date 十一月 2018
*
* \brief 封装的网络类工具
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <functional>

#include "buff.h"
#include "counter.h"
#include "message_dispatch.h"


using namespace std;
using namespace boost;
using namespace boost::asio;

typedef ip::tcp::socket _SocketType;
typedef boost::shared_ptr<_SocketType> _SocketPtr;
typedef boost::shared_ptr<io_service> _IoServicePtr;
class Session;
class SessionPool;
typedef boost::shared_ptr<Session> _SessionPtr;
typedef boost::shared_ptr<SessionPool> _SessionPoolPtr;

#define MAX_ONLINE_ROLE_NUM 100 // 最大上限数目


class SessionPool
{
public:
	int max_num = MAX_ONLINE_ROLE_NUM;
	std::map<int, _SessionPtr> all_session_map;

	SessionPool();
	~SessionPool(){};
	int join(_SessionPtr);
	void remove(int id);
};

int SessionPool::join(_SessionPtr session)
{
	if (this->all_session_map.size() >= this->max_num)
	{
		std::cout << "角色池已达上限" << std::endl;
		return -1;
	}
	int new_id = Counter::GetInstance()->get_count();
	all_session_map.insert(std::make_pair(new_id, session));
	printf("session %i has join\n", new_id);
	return new_id;
}

void SessionPool::remove(int id)
{
	std::map<int, _SessionPtr>::iterator key = all_session_map.find(id);
	if (key != all_session_map.end())
	{
		all_session_map.erase(key);
	}
	printf("session %i has remove from room, room size: %i\n", id, all_session_map.size());
}

SessionPool::SessionPool()
{
	// 初始化session id计数器
	Counter::New();
}


class Session :public boost::enable_shared_from_this<Session>
{
public:
	_SocketType socket;
	_SessionPoolPtr  session_pool;
	MessageDispatch* msg_patch_p;
	Buff read_buff;
	Buff write_buff;
	int id;

	Session(io_service& service, _SessionPoolPtr pool_ptr, MessageDispatch* patch_p) :socket(service), session_pool(pool_ptr), msg_patch_p(patch_p){};
	~Session(){};
	void join_pool();
	void handle_read();
	void handle_write();
	void on_read_head(const boost::system::error_code& err, std::size_t size);
	void on_read_body(const boost::system::error_code&, std::size_t);
	void deliver(const char* message);
};

// 加入角色池
void Session::join_pool()
{
	int id = this->session_pool->join(shared_from_this());
	this->id = id;
	this->handle_read();
}

// 绑定每个session的消息处理
void Session::handle_read()
{
	// 重置接受缓存
	this->read_buff.reset();
	boost::asio::async_read(
		this->socket,
		boost::asio::buffer(this->read_buff.head(), BUFF_HEAD_SIZE),
		boost::bind(&Session::on_read_head, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

// 接受消息头
void Session::on_read_head(const boost::system::error_code& err, std::size_t bytes)
{
	if (!err)
	{
		if (this->read_buff.decode_header())
		{
			boost::asio::async_read(
				this->socket,
				boost::asio::buffer(this->read_buff.body(), this->read_buff.recv_length), // 由消息体确定接下来消息体的长度
				boost::bind(&Session::on_read_body, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			std::cout << "recv msg size too big" << std::endl;
		}
	}
	else
	{
		this->session_pool->remove(this->id);
	}
}

// 接受消息体
void Session::on_read_body(const boost::system::error_code& err, std::size_t bytes)
{
	if (!err)
	{
		this->deliver(this->read_buff.body());
		this->handle_read();
	}
	else
	{
		this->session_pool->remove(this->id);
	}
}


void Session::deliver(const char* message)
{
	int* msg_id_p = (int*)message;
	const char* body = message + 4;
	this->msg_patch_p->Dispatch(*msg_id_p, body);
}




class Network
{
public:
	typedef void(*handle_func)(Network*  n_ptr, boost::system::error_code);

	int port;
	io_service service;
	ip::tcp::endpoint accept_port;
	ip::tcp::acceptor acceptor;
	_SocketPtr listen_sock;
	boost::shared_ptr<SessionPool> session_pool;
	MessageDispatch msg_dispatch;


	Network(int port);
	~Network(){};
	void listen();
	void connect_handle(_SessionPtr, boost::system::error_code);
	void run();
};

Network::Network(int port):
port(port),
service(boost::asio::io_service()),
accept_port(ip::tcp::endpoint(ip::tcp::v4(), this->port)),
acceptor(ip::tcp::acceptor(this->service, this->accept_port)),
listen_sock(new _SocketType(this->service)),
session_pool(new SessionPool),
msg_dispatch(MessageDispatch())
{
	// 协议分派事件
	msg_dispatch.InitEvent();
}

void Network::connect_handle(_SessionPtr session, boost::system::error_code e_code)
{
	if (!e_code)
	{
		session->join_pool();
	}
	this->listen();
}



void Network::listen()
{
	_SessionPtr session(new Session(this->service, this->session_pool, &this->msg_dispatch));

	this->acceptor.async_accept(session->socket, boost::bind(&Network::connect_handle, this, session, boost::asio::placeholders::error));
}

void Network::run()
{
	this->service.run();
}