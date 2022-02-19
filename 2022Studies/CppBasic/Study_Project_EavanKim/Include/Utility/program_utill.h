#ifndef	PROGRAM_UTILL_H__
#define PROGRAM_UTILL_H__

namespace Manager
{
	class Function
	{
	public:
		struct IOParam
		{
			IOParam(Study_Schedule* _schedule)
				: schedule(_schedule)
			{

			}
			Study_Schedule* schedule;
		};

		static void TestvoidFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//입출력 내용을 만들 컨테이너를 선언합니다.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo를 관리하는데 필요한 내용을 출력하고, 입력받을 내용을 결정합니다.
			//Localize에 저장되어있는 Manage 항목의 TITLE -> BODY -> END 순으로 출력을 지정합니다.
			//중간에 선택된 Task내용을 출력해서 어떤 내용이 선택되었는지 알려줍니다.
			OutPutSettings.push_back({ L"Function : TestvoidFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//화면을 한 번 지웁니다.
			Study_IO::ScreenClear();

			//세팅한 입출력 배열로 출력합니다.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void TestvoidintFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//입출력 내용을 만들 컨테이너를 선언합니다.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo를 관리하는데 필요한 내용을 출력하고, 입력받을 내용을 결정합니다.
			//Localize에 저장되어있는 Manage 항목의 TITLE -> BODY -> END 순으로 출력을 지정합니다.
			//중간에 선택된 Task내용을 출력해서 어떤 내용이 선택되었는지 알려줍니다.
			OutPutSettings.push_back({ L"Function : TestvoidintFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//화면을 한 번 지웁니다.
			Study_IO::ScreenClear();

			//세팅한 입출력 배열로 출력합니다.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void TestintvoidFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//입출력 내용을 만들 컨테이너를 선언합니다.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo를 관리하는데 필요한 내용을 출력하고, 입력받을 내용을 결정합니다.
			//Localize에 저장되어있는 Manage 항목의 TITLE -> BODY -> END 순으로 출력을 지정합니다.
			//중간에 선택된 Task내용을 출력해서 어떤 내용이 선택되었는지 알려줍니다.
			OutPutSettings.push_back({ L"Function : TestintvoidFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//화면을 한 번 지웁니다.
			Study_IO::ScreenClear();

			//세팅한 입출력 배열로 출력합니다.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void TestintintFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//입출력 내용을 만들 컨테이너를 선언합니다.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo를 관리하는데 필요한 내용을 출력하고, 입력받을 내용을 결정합니다.
			//Localize에 저장되어있는 Manage 항목의 TITLE -> BODY -> END 순으로 출력을 지정합니다.
			//중간에 선택된 Task내용을 출력해서 어떤 내용이 선택되었는지 알려줍니다.
			OutPutSettings.push_back({ L"Function : TestintintFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//화면을 한 번 지웁니다.
			Study_IO::ScreenClear();

			//세팅한 입출력 배열로 출력합니다.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void Delete(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//입출력 내용을 만들 컨테이너를 선언합니다.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo를 관리하는데 필요한 내용을 출력하고, 입력받을 내용을 결정합니다.
			//Localize에 저장되어있는 Manage 항목의 TITLE -> BODY -> END 순으로 출력을 지정합니다.
			//중간에 선택된 Task내용을 출력해서 어떤 내용이 선택되었는지 알려줍니다.
			OutPutSettings.push_back({ L"Function : Delete" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//화면을 한 번 지웁니다.
			Study_IO::ScreenClear();

			//세팅한 입출력 배열로 출력합니다.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
	};

	//전역 관리 객체를 한 번에 초기화 하는 함수입니다.
	static void Initialize(Manager::Study_Schedule* _TestSchedule = nullptr)
	{
		//프로그램 실행 경로를 가져와서 파일을 읽어들일 필요가 있는 대상은 해당 경로로부터 정보를 읽어들입니다.
		TCHAR programpath[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, programpath);

		Status::Initialize_Mgr();
		Study_Localize::Initialize_Mgr(programpath, L"Resource\\Localize_En");
		//Study_Localize::Initialize_Mgr(programpath, L"Resource\\Localize_Ko");
		Study_FunctionMgr::Initialize_Mgr();

		if (nullptr != _TestSchedule)
		{
			Study_FunctionMgr* GetMgr = Study_FunctionMgr::GetInstance();
			Manager::Function_Struct createfunction0(L"Func0", Function::TestvoidFunction);
			GetMgr->AddFunction(createfunction0);
			Manager::Function_Struct createfunction1(L"Func1", Function::TestvoidintFunction);
			GetMgr->AddFunction(createfunction1);
			Manager::Function_Struct createfunction2(L"Func2", Function::TestintvoidFunction);
			GetMgr->AddFunction(createfunction2);
			Manager::Function_Struct createfunction3(L"Func3", Function::TestintintFunction);
			GetMgr->AddFunction(createfunction3);
			createfunction3.key = L"Delete";
			createfunction3.function = Function::Delete;
			GetMgr->AddFunction(createfunction3);

			Function_Parameter_Result DoingFunction(L"Func0", nullptr, new Function::IOParam(_TestSchedule));
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Func1";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Func2";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Func3";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Delete";
			GetMgr->Do(&DoingFunction);

			GetMgr->RemoveFunction(L"Delete");

			DoingFunction.key = L"Func0";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Func1";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Func2";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Func3";
			GetMgr->Do(&DoingFunction);
			DoingFunction.key = L"Delete";
			GetMgr->Do(&DoingFunction);
		}
	}

	//전역 관리 객체를 한 번에 해제 하는 함수입니다.
	static void Release()
	{
		//해제는 초기화의 역순으로 하는편이 안전합니다.
		//왜냐하면, 나중에 초기화 될 수록 먼저 초기화 된 대상에 대해 종속성을 가질 수 있기 때문입니다.
		Study_FunctionMgr* FunctionMgr = Study_FunctionMgr::GetInstance();
		if (FunctionMgr)
			FunctionMgr->Release();
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		if(LocalizeMgr)
			LocalizeMgr->Release();
		Status* StatusMgr = Status::GetInstance();
		if(StatusMgr)
			StatusMgr->Release();
	}
}

#endif