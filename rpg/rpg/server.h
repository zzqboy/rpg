/*!
 * \file server.h
 *
 * \author ziquan
 * \date ���� 2019
 *
 * \brief ��Ϸ����������ĸ�������
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
	// ��������
	this->network = new Network(9000);
	this->network->listen();
	// ���ݿ�
	DBWork::GetInstance()->New();
}

Server::~Server()
{

}

void Server::run()
{
	this->network->run();
	DBWork::GetInstance()->run();
}