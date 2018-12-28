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


class Session :public boost::enable_shared_from_this<Session>
{
public:
	_SocketType socket;
	_SessionPoolPtr  role_pool;
	Buff read_buff;
	Buff write_buff;
	int id;

	Session(io_service& service, _SessionPoolPtr pool_ptr) :socket(service), role_pool(pool_ptr){};
	~Session(){};
	void handle_read();
	void handle_write();
	void on_read_head(const boost::system::error_code& err, std::size_t size);
	void on_read_body(boost::system::error_code err);
	void deliver(const char* message);
};

// 绑定每个session的消息处理
void Session::handle_read()
{
	int id = this->role_pool->join(shared_from_this());
	this->id = id;
	// 重置接受缓存
	boost::asio::async_read(
		this->socket,
		boost::asio::buffer(this->read_buff.head(), BUFF_HEAD_SIZE),
		boost::bind(&Session::on_read_head, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

// 接受消息头
void Session::on_read_head(const boost::system::error_code& err, std::size_t bytes)
{
	if (!err && this->read_buff.decode_header())
	{
		std::cout << "head msg: " << this->read_buff.recv_length << std::endl;
		boost::asio::async_read(
			this->socket,
			boost::asio::buffer(this->read_buff.body(), BUFF_BODY_SIZE),
			boost::bind(&Session::on_read_body, shared_from_this(), boost::asio::placeholders::error));
	}
	else
	{
		this->role_pool->remove(this->id);
	}
}

// 接受消息体
void Session::on_read_body(boost::system::error_code err)
{
	if (!err)
	{
		this->deliver(this->read_buff.body());
		std::cout << "head msg: " << this->read_buff.recv_length << std::endl;
		boost::asio::async_read(
			this->socket,
			boost::asio::buffer(this->read_buff.m_char, BUFF_HEAD_SIZE),
			boost::bind(&Session::on_read_head, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		this->role_pool->remove(this->id);
	}
}


void Session::deliver(const char* message)
{
	std::cout << message << std::endl;
}




class Network
{
public:
	typedef void(*handle_func)(Network*  n_ptr, boost::system::error_code);

	int port;
	io_service& service;
	ip::tcp::endpoint accept_port;
	ip::tcp::acceptor acceptor;
	_SocketPtr listen_sock;
	boost::shared_ptr<SessionPool> role_pool;


	Network(int port, io_service& io_server);
	~Network(){};
	void listen();
	void connect_handle(_SessionPtr, boost::system::error_code);
};

Network::Network(int port, io_service& io_server) :
port(port),
service(io_server),
accept_port(ip::tcp::endpoint(ip::tcp::v4(), this->port)),
acceptor(ip::tcp::acceptor(this->service, this->accept_port)),
listen_sock(new _SocketType(this->service)),
role_pool(new SessionPool)
{
}

void Network::connect_handle(_SessionPtr session, boost::system::error_code e_code)
{
	if (!e_code)
	{
		session->handle_read();
	}
	this->listen();
}



void Network::listen()
{
	_SessionPtr session(new Session(this->service, this->role_pool));

	this->acceptor.async_accept(session->socket, boost::bind(&Network::connect_handle, this, session, boost::asio::placeholders::error));
}

