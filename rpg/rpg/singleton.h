/*!
 * \file singleton.h
 *
 * \author ziquan
 * \date 十一月 2018
 *
 * \brief 单例模式
 * 可以使用用锁的方式，但是对性能有影响
 * 也可以在多线程启动前去主动new一个，在多线程的时候就自动保证了线程安全
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