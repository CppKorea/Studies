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

//프로그램에서 참조하는 헤더
//모아서 정렬한 헤더 하나를 사용하고 있으므로 PCH(Pre-Compiled Header) 라고 하는 형태로 쓰기 편합니다.
//이는 Header 순서를 매 빌드마다 정리하면서 새로 빌드하는 절차를 없애기 위해 이미 완성된 헤더 빌드 정보를 가져다 쓰는 동작입니다.
//pch.h를 진짜 쓰는것은 제약을 많이 생성하므로 우선은 건너뜁니다.
#include "headers_custom.h"

//HDD에 저장된 프로그램을 Memory에 올리면서 호출하도록 되어있는 코드입니다.
int main()
{
	int ExitCode = 0;
	Manager::Initialize();
	Manager::Status* StatusMgr = Manager::Status::GetInstance();

	try
	{
		while (StatusMgr->CheckProgramRunSanity())
		{
			//실행 루프
		}
	}
	catch (std::exception _excep)
	{
		ExitCode = 1;
		StatusMgr->SetProgramRunState(Manager::PROGRAM_RUN_STATE::EXCEPTION);
	}
	catch (...)
	{
		ExitCode = 2;
		StatusMgr->SetProgramRunState(Manager::PROGRAM_RUN_STATE::EXCEPTION);
	}

	Manager::Release();

	return ExitCode;
}
