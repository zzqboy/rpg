/*!
* \file Network.h
*
* \author ziquan
* \date 十一月 2018
*
* \brief 封装的网络类工具
*/

#ifndef _network_
#define _network_
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
	void _real_run();
};
#endif