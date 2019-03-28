/*!
 * \file server.h
 *
 * \author ziquan
 * \date 二月 2019
 *
 * \brief 游戏服务器管理的各个服务
 */
#include "singleton.h"
#include "network.h"

class Server :public Singleton<Server>
{
public:
	Server();
	~Server();
	void run();
private:
	Network* network;
};

Server::Server()
{
	// 监听网络
	this->network = new Network(9000);
	this->network->listen();
}

Server::~Server()
{

}

void Server::run()
{
	this->network->run();
}