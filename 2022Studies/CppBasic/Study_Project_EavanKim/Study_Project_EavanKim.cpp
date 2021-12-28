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
	//ExitCode는 Windows OS에서 이 프로그램이 종료했을때 올바르게 종료되었나 아닌가를 판단하는데 사용됩니다.
	//0은 아무 이상 없이 잘 종료되었다는 표시입니다.
	//Windows에서 사용하는 에러코드를 따르므로 MSDN등에서 에러코드를 찾아보고 올바르게 처리하거나, 잘 정리해서 사용해야 합니다.
	int ExitCode = 0;
	//전역에서 사용되는 Manager Namespace아래의 객체를 생성하도록 지시합니다.
	Manager::Initialize();

	//프로그램은 기본적으로 Status가 정상이 아니라면(할당에 실패해서 nullptr이 되어버린다면) 종료되도록 false상태로 만듭니다.
	bool ProgramRun = false;

	//Manager::Initialize()에서 생성된 Status 객체의 포인터를 사용하기 전에 확인합니다.
	//일회성으로 사용하지 않는다면 단일자인 Status가 불특정 순간에 Release가 될 만한 일(크래시에 의한 즉시 해제)이 발생하면 댕글링 포인터를 물게 됩니다.
	Manager::Status* StatusMgr = Manager::Status::GetInstance();
	if (nullptr != StatusMgr)
		ProgramRun = StatusMgr->CheckProgramRunSanity();	//실행이 가능한 상태가 확인되면 여기서 프로그램 실행 체크가 True가 됩니다.

	try
	{
		while (ProgramRun)
		{
			//실행 루프


			//Manager::Initialize()에서 생성된 Status 객체의 포인터를 사용하기 전에 확인합니다.
			//일회성으로 사용하지 않는다면 단일자인 Status가 불특정 순간에 Release가 될 만한 일(크래시에 의한 즉시 해제)이 발생하면 댕글링 포인터를 물게 됩니다.
			Manager::Status* StatusMgr = Manager::Status::GetInstance();
			if (nullptr != StatusMgr)
				ProgramRun = StatusMgr->CheckProgramRunSanity();	//실행이 가능한 상태가 확인되면 여기서 프로그램 실행 체크가 True가 됩니다.
		}
	}
	catch (std::exception _excep) //여러가지 에러 객체중 std::excpetion을 상속한 객체가 발생되는 경우 여기로 진입합니다.
	{
		ExitCode = 1;//임의의 종료 코드입니다. 이렇게 사용하면 Windows에서 제공해주는 종료코드별 에러 분석을 오염시키므로 코드 작성자가 알아서 잘 처리해야합니다.
		StatusMgr->SetProgramRunState(Manager::PROGRAM_RUN_STATE::EXCEPTION);
	}
	catch (...) //std::exception을 상속하지 않은 에러는 이곳으로 내려옵니다.
	{
		ExitCode = 2;//임의의 종료 코드입니다. 이렇게 사용하면 Windows에서 제공해주는 종료코드별 에러 분석을 오염시키므로 코드 작성자가 알아서 잘 처리해야합니다.
		StatusMgr->SetProgramRunState(Manager::PROGRAM_RUN_STATE::EXCEPTION);
	}

	//전역에서 사용되는 Manager Namespace아래의 객체를 정리하도록 지시합니다.
	Manager::Release();

	//Windows OS에 종료 코드를 알려주면서 최종적으로 프로그램이 종료됩니다.
	return ExitCode;
}
