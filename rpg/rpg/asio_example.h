#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include<boost/enable_shared_from_this.hpp>
#include<iostream>
using namespace boost::asio;
using  boost::asio::ip::tcp; //��
class client_session :public boost::enable_shared_from_this<client_session>
{
private:
	char read_buf_[512];                               //����һ��char
	tcp::socket socket_;                               //����һ��socket�Ķ���
public:

	client_session(io_service &ioservice)              //��ioservic���� socket�˿�
		: socket_(ioservice)                           // �������������ʼ���׽��ֶ���
	{
	}
	tcp::socket&socket()                                 //����˽�б���socket_�Ľӿ�
	{
		return socket_;
	}
	void start()                                          //�ͻ���ִ�к���       
	{
		async_write(socket_, boost::asio::buffer("��ӭ���ӷ�����"),
			boost::bind(&client_session::write_handle, shared_from_this(), _1));
		memset(read_buf_, 0, sizeof(read_buf_));                           //������
		socket_.async_read_some(boost::asio::buffer(read_buf_, 512),        //�첽��ȡ��������ȡread_buf����
			boost::bind(&client_session::read_handle, shared_from_this(),           //��bind
			/*	boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred*/
			_1, _2
			));
	}
	void read_handle(const boost::system::error_code&error, size_t bytes_transferred)          //������
	{
		if (!error)                                                                       //�Ӳ����ж�ȡ
		{
			std::cout << "����Ϊ:" << read_buf_ << "����Ϊ" << bytes_transferred << std::endl;
			async_write(socket_, boost::asio::buffer(read_buf_, bytes_transferred),
				boost::bind(&client_session::write_handle, shared_from_this(), _1));  //�ص�


		}
	}
	void write_handle(const boost::system::error_code& error)                       //д����
	{
		if (!error)
		{
			memset(read_buf_, 0, sizeof(read_buf_));
			socket_.async_read_some(boost::asio::buffer(read_buf_, 512),          //����start
				boost::bind(&client_session::read_handle, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}
protected:
};

class async_server                                           //��������
{
private:
	io_service&  io_service_;                            //�첽���񹤾�  io_service����
	tcp::acceptor acceptor_;                             //������ ����

public:
	async_server(io_service &ioservice, const tcp::endpoint endpoint)            //endpoint�Ƕ˵�   ���� ����һ��io���񹤾� ��һ��endpoint
		:io_service_(ioservice)                                                //���캯�� ��ʼ��ioservice�����accepotr
		, acceptor_(ioservice, endpoint)
	{
		start_accept();                                                        //���캯�� ��ִ���첽������
	}
	void start_accept()
	{
		std::cout << "׼����ʼ��������" << std::endl;                            //��ʾ
		boost::shared_ptr<client_session>new_session(new client_session(io_service_));//new һ���ͻ��˶���
		acceptor_.async_accept(new_session->socket(), boost::bind(&async_server::accept_handle, this, new_session, _1));//���ص������ҽ���ϵͳ�ϣ�ʲôʱ��ϵͳ֪����������ˣ��ᷴ��֪ͨ�ص�����																												//���ص������ҽ���ϵͳ�ϣ�ʲôʱ��ϵͳ֪����������ˣ��ᷴ��֪ͨ�ص�����
	}
	void accept_handle(boost::shared_ptr<client_session>client, const boost::system::error_code&error)       //��------ϵͳ�����ģ��������Ǵ�����
	{
		if (!error)                                                                                          //
		{
			std::cout << "���ӵ�ַ��" << client->socket().remote_endpoint().address()
				<< "���Ӷ˿� " << client->socket().remote_endpoint().port() << std::endl;
			client->start();

		}
		start_accept();
	}
protected:
};
int main()
{
	io_service service;                               //service����
	ip::tcp::endpoint endpoint(tcp::v4(), 8888);     //����һ��enpotion�������ڹ��� �첽����������
	boost::shared_ptr<async_server>service_(new async_server(service, endpoint));
	service.run();
	getchar();
	return 0;
}
