/*!
 * \file test_network.h
 *
 * \author ziquan
 * \date ʮ���� 2018
 *
 * \brief ��������
 */
#include "network.h"


void test_network()
{
	Network my_network(8001);
	my_network.listen();
	my_network.run();
}
