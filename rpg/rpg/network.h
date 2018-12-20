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
#include <iostream>
#include <functional>

#include "buff.h"

using namespace std;
using namespace boost;
using namespace boost::asio;

typedef ip::tcp::socket _SocketType;
typedef boost::shared_ptr<_SocketType> _SocketPtr;
typedef boost::shared_ptr<io_service> _IoServicePtr;
class Session;

#define MAX_ONLINE_ROLE_NUM 100 // 最大上限数目

class SessionPool
{
public:
	int max_num = MAX_ONLINE_ROLE_NUM;
	std::map<int, Session*> all_session_map;

	void join(Session*);
};

void SessionPool::join(Session* sock_ptr)
{
	if (this->all_session_map.size() >= this->max_num)
	{
		std::cout << "角色池已达上限" << std::endl;
		return;
	}

}


class Session
{
public:
	_SocketType socket;
	SessionPool*  role_pool;
	Buff read_buff;
	Buff write_buff;

	Session(_IoServicePtr service_ptr) :socket(*service_ptr){};
	void handle_read();
	void handle_write();
	void on_read(boost::system::error_code err, std::size_t bytes);
};

// 绑定每个session的接受处理
void Session::handle_read()
{
	//this->socket.async_read_some(boost::asio::buffer(this->read_buff.m_char), boost::bind(&Session::on_read, this, _1, _2));
	boost::asio::async_read(this->socket, boost::asio::buffer(this->read_buff.m_char), boost::bind(&Session::on_read, this, _1, _2));
}

void Session::on_read(boost::system::error_code err, std::size_t bytes)
{
	if (err)
	{
		printf("on_read error %i", err);
		return;
	}
	else
	{
		std::cout << "recv bytes: " << bytes << std::endl;
		string msg(this->read_buff.m_char, bytes);
		std::cout << "recv: " << msg << std::endl;
		this->handle_read();
	}
}



class Network
{
public:
	typedef void(*handle_func)(Network*  n_ptr, boost::system::error_code);

	int port;
	_IoServicePtr service;
	boost::shared_ptr<ip::tcp::endpoint> accept_port;
	boost::shared_ptr<ip::tcp::acceptor> acceptor;
	_SocketPtr listen_sock;
	boost::shared_ptr<SessionPool> role_pool;


	Network(int port);
	~Network(){};
	void listen();
	void run();
	void connect_handle(boost::system::error_code);
};

Network::Network(int port) :
port(port),
service(new boost::asio::io_service()),
accept_port(new ip::tcp::endpoint(ip::tcp::v4(), this->port)),
acceptor(new ip::tcp::acceptor(*this->service, *this->accept_port)),
listen_sock(new _SocketType(*this->service)),
role_pool(new SessionPool)
{
}

void Network::connect_handle(boost::system::error_code e_code)
{
	// 把每个连接封装为一个session并放入玩家池
	if (!e_code)
	{
		std::cout << "接受请求" << std::endl;
		Session session(this->service);
		session.handle_read();
		this->role_pool->join(&session);

	}
	this->listen();
}



void Network::listen()
{
	(*(this->acceptor)).async_accept(*this->listen_sock, boost::bind(&Network::connect_handle, this, boost::asio::placeholders::error));
}

void Network::run()
{
	this->service->run();
}

