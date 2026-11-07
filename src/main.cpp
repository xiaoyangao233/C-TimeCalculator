#include <windows.h>
#include"SelfTest.h"
#include"ConsoleUI.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);   // 输出用 UTF-8
	SetConsoleCP(CP_UTF8);         // 输入用 UTF-8（可选）

#ifdef _DEBUG
	runSelfTest();
#endif


	ConsoleUI ui;
	ui.run();

	return 0;

}