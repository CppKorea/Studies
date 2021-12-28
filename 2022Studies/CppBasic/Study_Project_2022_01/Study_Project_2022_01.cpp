/*
* C++ Korea 2022년 1분기 스터디
* C++ Basics
* 
*	Manager
*		I/O
*			Console
*			File
*		Schedule
*			Task
*/

#include "headers_custom.h"

int main()
{
	int ExitCode = 0;
	Manager::Initialize();
	Manager::Status* StatusMgr = Manager::Status::GetInstance();

	try
	{
		while (StatusMgr->CheckNormalState())
		{
			//실행 루프
			StatusMgr->SetProgramState(Manager::PROGRAM_STATE::EXIT);
		}
	}
	catch (std::exception _excep)
	{
		ExitCode = 1;
	}
	catch (...)
	{
		ExitCode = 2;
	}

	Manager::Release();

	return ExitCode;
}
