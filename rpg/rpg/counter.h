/*!
 * \file counter.h
 *
 * \author ziquan
 * \date ʮ���� 2018
 *
 * \brief ������
 */
#include "singleton.h"

// ���������ļ�����
class Counter:public Singleton<Counter>
{
private:
	int last_num = 0;
public:
	Counter(){};
	~Counter(){};

	int get_count()
	{
		int now = last_num;
		last_num += 1;
		return now;
	}
};
