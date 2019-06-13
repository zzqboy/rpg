#include "network.h"

/************************************************************************/
/* 连接池                                                                     */
/************************************************************************/
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




void Session::join_pool()
{
	int id = this->session_pool->join(shared_from_this());
	this->id = id;
	this->handle_read();
}

void Session::handle_read()
{
	// 重置接受缓存
	this->read_buff.reset();
	boost::asio::async_read(
		this->socket,
		boost::asio::buffer(this->read_buff.head(), BUFF_HEAD_SIZE),
		boost::bind(&Session::on_read_head, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

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


/************************************************************************/
/* 网络类                                                                     */
/************************************************************************/
Network::Network(int port) :
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

void Network::_real_run()
{
	this->service.run();
}

void Network::run()
{
	thread* t = new thread(&Network::_real_run, this);
	t->detach();
}

