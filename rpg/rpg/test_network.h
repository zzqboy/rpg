/*!
 * \file test_network.h
 *
 * \author ziquan
 * \date Ê®¶şÔÂ 2018
 *
 * \brief ²âÊÔÍøÂç
 */
#include "network.h"


void test_network()
{
	Network my_network(8001);
	my_network.listen();
	my_network.run();
}
