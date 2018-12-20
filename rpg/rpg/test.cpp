#include <boost/asio.hpp>
#include <iostream>
#include "network.h"
using namespace std;
using namespace boost::system;


void Print(Network* n_ptr, boost::system::error_code ec) {
	if (ec)
	{
		std::cerr << "From" << n_ptr->listen_sock->remote_endpoint().address() << " error: " << boost::system::system_error(ec).what() << std::endl;
	}
	std::cout << "hello world" << std::endl;
	n_ptr->run();
}

int main() {
	//boost::asio::io_service ioc;
	//boost::asio::deadline_timer timer(ioc, boost::posix_time::seconds(3));
	//timer.async_wait(&Print);
	//ioc.run();
	//return 0;
	Network my_network(8001);
	my_network.listen();
	my_network.run();
}