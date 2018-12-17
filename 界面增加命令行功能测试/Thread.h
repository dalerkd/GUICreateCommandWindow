#pragma once

#include "Windows.h"
#include <exception>

/*
注意:
本类可自动管理释放时机.
勿主动释放调用delete.

本类实现了线程的自动管理

*/
class Thread
{
public:
	virtual ~Thread();
public:
	/*
	启动线程相关
	返回TID,失败返回0
	*/
	unsigned long start()throw (std::exception);
	/*
	将你待执行的代码.重载它
	*/
	virtual void run() = 0;

	static DWORD WINAPI StaticThreadStart(void* param);
	
	unsigned long/*DWORD*/ GetMyThreadID() {
		return m_threadID;
	}
	HANDLE GetMyThreadHandle()
	{
		return m_threadHandle;
	}
private:
	unsigned long m_threadID = 0;
	HANDLE m_threadHandle = 0;//创建失败时为0

};


