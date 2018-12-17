#pragma once

#include "Thread.h"
#include <cstdio>

class ConsoleManager : public Thread
{
public:
	ConsoleManager()
	{
		CreateConsole();
	}
	~ConsoleManager()
	{
		PhCloseDebugConsole();
	};
private:
	/*
	 * ����һ���¿���̨����
	 */
	void CreateConsole()
	{
		if (AllocConsole())
		{
			//���� �ر�,��Ϊ�޷���������¼�
			HMENU menu;
			menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			EnableMenuItem(menu, SC_CLOSE, MF_GRAYED | MF_DISABLED);
			DeleteMenu(menu, SC_CLOSE, 0);

			// Set a handler so we can catch Ctrl+C and Ctrl+Break.
			SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
			FILE* temp=nullptr;

			freopen_s(&temp,"CONOUT$", "w", stdout);
			freopen_s(&temp,"CONOUT$", "w", stderr);
			freopen_s(&temp,"CONIN$", "r", stdin);

			start();
		}
		else
		{//�Ѿ��������ö�
			HWND consoleWindow;

			consoleWindow = GetConsoleWindow();

			// Console window already exists, so bring it to the top.
			if (IsIconic(consoleWindow))
				ShowWindow(consoleWindow, SW_RESTORE);
			else
				BringWindowToTop(consoleWindow);

			return;

		}
	}
protected:
	static VOID PhCloseDebugConsole(
		VOID
	)
	{
		FILE* temp=nullptr;
		freopen_s(&temp,"NUL", "w", stdout);
		freopen_s(&temp,"NUL", "w", stderr);
		freopen_s(&temp,"NUL", "r", stdin);
		FreeConsole();
	}
	//BOOL
	//(WINAPI *PHANDLER_ROUTINE)(
	//	_In_ DWORD CtrlType
	//	);
	static BOOL WINAPI ConsoleHandlerRoutine(
		_In_ DWORD dwCtrlType
	)
	{
		switch (dwCtrlType)
		{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
			PhCloseDebugConsole();
			return TRUE;
		}

		return FALSE;
	}


};

