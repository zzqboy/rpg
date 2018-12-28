#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include<boost/enable_shared_from_this.hpp>
#include<iostream>
using namespace boost::asio;
using  boost::asio::ip::tcp; //子
class client_session :public boost::enable_shared_from_this<client_session>
{
private:
	char read_buf_[512];                               //声明一个char
	tcp::socket socket_;                               //声明一个socket的对象
public:

	client_session(io_service &ioservice)              //用ioservic构造 socket端口
		: socket_(ioservice)                           // 构造就是用来初始化套接字对象
	{
	}
	tcp::socket&socket()                                 //返回私有变量socket_的接口
	{
		return socket_;
	}
	void start()                                          //客户端执行函数       
	{
		async_write(socket_, boost::asio::buffer("欢迎连接服务器"),
			boost::bind(&client_session::write_handle, shared_from_this(), _1));
		memset(read_buf_, 0, sizeof(read_buf_));                           //清数组
		socket_.async_read_some(boost::asio::buffer(read_buf_, 512),        //异步读取函数，读取read_buf数组
			boost::bind(&client_session::read_handle, shared_from_this(),           //绑定bind
			/*	boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred*/
			_1, _2
			));
	}
	void read_handle(const boost::system::error_code&error, size_t bytes_transferred)          //读函数
	{
		if (!error)                                                                       //从参数中读取
		{
			std::cout << "内容为:" << read_buf_ << "长度为" << bytes_transferred << std::endl;
			async_write(socket_, boost::asio::buffer(read_buf_, bytes_transferred),
				boost::bind(&client_session::write_handle, shared_from_this(), _1));  //回掉


		}
	}
	void write_handle(const boost::system::error_code& error)                       //写函数
	{
		if (!error)
		{
			memset(read_buf_, 0, sizeof(read_buf_));
			socket_.async_read_some(boost::asio::buffer(read_buf_, 512),          //调用start
				boost::bind(&client_session::read_handle, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}
protected:
};

class async_server                                           //服务器端
{
private:
	io_service&  io_service_;                            //异步服务工具  io_service对象
	tcp::acceptor acceptor_;                             //接受器 对象

public:
	async_server(io_service &ioservice, const tcp::endpoint endpoint)            //endpoint是端点   构造 接受一个io服务工具 和一个endpoint
		:io_service_(ioservice)                                                //构造函数 初始化ioservice对象和accepotr
		, acceptor_(ioservice, endpoint)
	{
		start_accept();                                                        //构造函数 即执行异步服务器
	}
	void start_accept()
	{
		std::cout << "准备开始接受连接" << std::endl;                            //提示
		boost::shared_ptr<client_session>new_session(new client_session(io_service_));//new 一个客户端对象
		acceptor_.async_accept(new_session->socket(), boost::bind(&async_server::accept_handle, this, new_session, _1));//将回调函数挂接在系统上，什么时候系统知道接收完毕了，会反向通知回掉函数																												//将回调函数挂接在系统上，什么时候系统知道接收完毕了，会反向通知回掉函数
	}
	void accept_handle(boost::shared_ptr<client_session>client, const boost::system::error_code&error)       //《------系统出发的，不是我们触发的
	{
		if (!error)                                                                                          //
		{
			std::cout << "连接地址：" << client->socket().remote_endpoint().address()
				<< "连接端口 " << client->socket().remote_endpoint().port() << std::endl;
			client->start();

		}
		start_accept();
	}
protected:
};
int main()
{
	io_service service;                               //service对象
	ip::tcp::endpoint endpoint(tcp::v4(), 8888);     //构造一个enpotion对象用于构造 异步服务器对象
	boost::shared_ptr<async_server>service_(new async_server(service, endpoint));
	service.run();
	getchar();
	return 0;
}
