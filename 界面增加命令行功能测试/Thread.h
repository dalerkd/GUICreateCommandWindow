#pragma once

#include "Windows.h"
#include <exception>

/*
ע��:
������Զ������ͷ�ʱ��.
�������ͷŵ���delete.

����ʵ�����̵߳��Զ�����

*/
class Thread
{
public:
	virtual ~Thread();
public:
	/*
	�����߳����
	����TID,ʧ�ܷ���0
	*/
	unsigned long start()throw (std::exception);
	/*
	�����ִ�еĴ���.������
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
	HANDLE m_threadHandle = 0;//����ʧ��ʱΪ0

};


