/*!
 * \file singleton.h
 *
 * \author ziquan
 * \date ʮһ�� 2018
 *
 * \brief ����ģʽ
 * ����ʹ�������ķ�ʽ�����Ƕ�������Ӱ��
 * Ҳ�����ڶ��߳�����ǰȥ����newһ�����ڶ��̵߳�ʱ����Զ���֤���̰߳�ȫ
 */
#ifndef _singleton_
#define _singleton_

template<class T>
class Singleton{
protected:
	static T* instance;
	Singleton(){};
	~Singleton(){};
public:
	static T* GetInstance()
	{
		return instance;
	}

	static void New()
	{
		instance = new T();
	}

	static void Delete()
	{
		if (instance != NULL)
		{
			delete instance;
		}
	}
};

template<class T>
T* Singleton<T>::instance;

#endif