#pragma once
#include "ConsoleManager.h"
/*
 * ����Ƶ�ȱ��:
 * ͨ��Ctrl+C���޷��˳������̵߳ġ������̻߳��ǻ��������
 *
 *
 */



class DebugConsole :
	public ConsoleManager
{
public:
	DebugConsole();
	~DebugConsole();
private:
	void run() override
	{
		BOOLEAN exit = FALSE;
		wprintf(L"Press Ctrl+C or type \"exit\" to close the debug console. Type \"help\" for a list of commands.\n");
		while (!exit)
		{
			const wchar_t* delims = L" \t";
			const wchar_t* commandDebugOnly = L"This command is not available on non-debug builds.\n";

			WCHAR line[201];
			ULONG inputLength;
			PWSTR context;
			PWSTR command;
			memset(line, 0, sizeof(line));
			wprintf(L"dbg>");

			if (!fgetws(line, sizeof(line) / 2 - 1, stdin))
				break;//��Control+Cʱ�˳�
				

			// Remove the terminating new line character.

			inputLength = (ULONG)wcslen(line);//ע����ܳ���

			if (inputLength != 0)
				line[inputLength - 1] = 0;

			context = NULL;
			command = wcstok_s(line, delims, &context);

			if (!command)
			{
				continue;
			}
			else if (!wcscmp(command, L"help"))
			{
				wprintf(
					L"Commands:\n"
					L"exit\n"
					L"testperf\n"
					L"testlocks\n"
					L"stats\n"
					L"objects [type-name-filter]\n"
					L"objtrace object-address\n"
					L"objmksnap\n"
					L"objcmpsnap\n"
					L"objmknew\n"
					L"objdelnew\n"
					L"objviewnew\n"
					L"dumpobj\n"
					L"dumpautopool\n"
					L"threads\n"
					L"provthreads\n"
					L"workqueues\n"
					L"procrecords\n"
					L"procitem\n"
					L"uniquestr\n"
					L"enableleakdetect\n"
					L"leakdetect\n"
					L"mem\n"
				);
			}
			else if (!wcscmp(command, L"exit"))
			{
				PhCloseDebugConsole();
				exit = TRUE;
			}
			else
			{
				wprintf(L"Unrecognized command.\n");
				 // get rid of the compiler warning about the label being unreferenced
			}
		}
	}

};

