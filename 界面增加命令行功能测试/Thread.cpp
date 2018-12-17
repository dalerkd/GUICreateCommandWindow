#include "stdafx.h"
#include "Thread.h"


Thread::~Thread()
{
	if (m_threadHandle != INVALID_HANDLE_VALUE) {

		CloseHandle(m_threadHandle);
	}

}

unsigned long Thread::start()throw(std::exception)
{
	DWORD ThreadID=0;
	HANDLE threadHandle = CreateThread(0,0, StaticThreadStart,(void*)this,0,&ThreadID);
	m_threadHandle = threadHandle;
	m_threadID = ThreadID;
	
	if (threadHandle == 0)
	{
		throw std::exception("CreateThreadFault");
		return 0;
	}
	return ThreadID;
}

DWORD WINAPI Thread::StaticThreadStart(void* param)
{
	if (!param)
	{
		return -1;
	}
	Thread* This = (Thread*)param;
	This->run();
	delete(This);
	This = nullptr;
	return true;
}