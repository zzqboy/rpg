/*!
 * \file server.h
 *
 * \author ziquan
 * \date ���� 2019
 *
 * \brief ��Ϸ����������ĸ�������
 */
#include "network.h"

class Server
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
	// ��������
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