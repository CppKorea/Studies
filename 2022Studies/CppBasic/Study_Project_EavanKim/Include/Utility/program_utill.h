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

			//����� ������ ���� �����̳ʸ� �����մϴ�.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo�� �����ϴµ� �ʿ��� ������ ����ϰ�, �Է¹��� ������ �����մϴ�.
			//Localize�� ����Ǿ��ִ� Manage �׸��� TITLE -> BODY -> END ������ ����� �����մϴ�.
			//�߰��� ���õ� Task������ ����ؼ� � ������ ���õǾ����� �˷��ݴϴ�.
			OutPutSettings.push_back({ L"Function : TestvoidFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//ȭ���� �� �� ����ϴ�.
			Study_IO::ScreenClear();

			//������ ����� �迭�� ����մϴ�.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void TestvoidintFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//����� ������ ���� �����̳ʸ� �����մϴ�.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo�� �����ϴµ� �ʿ��� ������ ����ϰ�, �Է¹��� ������ �����մϴ�.
			//Localize�� ����Ǿ��ִ� Manage �׸��� TITLE -> BODY -> END ������ ����� �����մϴ�.
			//�߰��� ���õ� Task������ ����ؼ� � ������ ���õǾ����� �˷��ݴϴ�.
			OutPutSettings.push_back({ L"Function : TestvoidintFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//ȭ���� �� �� ����ϴ�.
			Study_IO::ScreenClear();

			//������ ����� �迭�� ����մϴ�.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void TestintvoidFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//����� ������ ���� �����̳ʸ� �����մϴ�.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo�� �����ϴµ� �ʿ��� ������ ����ϰ�, �Է¹��� ������ �����մϴ�.
			//Localize�� ����Ǿ��ִ� Manage �׸��� TITLE -> BODY -> END ������ ����� �����մϴ�.
			//�߰��� ���õ� Task������ ����ؼ� � ������ ���õǾ����� �˷��ݴϴ�.
			OutPutSettings.push_back({ L"Function : TestintvoidFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//ȭ���� �� �� ����ϴ�.
			Study_IO::ScreenClear();

			//������ ����� �迭�� ����մϴ�.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void TestintintFunction(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//����� ������ ���� �����̳ʸ� �����մϴ�.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo�� �����ϴµ� �ʿ��� ������ ����ϰ�, �Է¹��� ������ �����մϴ�.
			//Localize�� ����Ǿ��ִ� Manage �׸��� TITLE -> BODY -> END ������ ����� �����մϴ�.
			//�߰��� ���õ� Task������ ����ؼ� � ������ ���õǾ����� �˷��ݴϴ�.
			OutPutSettings.push_back({ L"Function : TestintintFunction" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//ȭ���� �� �� ����ϴ�.
			Study_IO::ScreenClear();

			//������ ����� �迭�� ����մϴ�.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
		static void Delete(Function_Parameter_Result* _InOut)
		{
			IOParam* Parameter = (IOParam*)_InOut->parameter;
			Study_Schedule* GetSchedule = Parameter->schedule;

			//����� ������ ���� �����̳ʸ� �����մϴ�.
			std::vector<Study_Schedule::Schedule_IO_Setup> OutPutSettings;

			//ToDo�� �����ϴµ� �ʿ��� ������ ����ϰ�, �Է¹��� ������ �����մϴ�.
			//Localize�� ����Ǿ��ִ� Manage �׸��� TITLE -> BODY -> END ������ ����� �����մϴ�.
			//�߰��� ���õ� Task������ ����ؼ� � ������ ���õǾ����� �˷��ݴϴ�.
			OutPutSettings.push_back({ L"Function : Delete" });
			OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_SUSPEND, L"SUSPEND" });

			//ȭ���� �� �� ����ϴ�.
			Study_IO::ScreenClear();

			//������ ����� �迭�� ����մϴ�.
			GetSchedule->ProcessIOSetupList(OutPutSettings);
		}
	};

	//���� ���� ��ü�� �� ���� �ʱ�ȭ �ϴ� �Լ��Դϴ�.
	static void Initialize(Manager::Study_Schedule* _TestSchedule = nullptr)
	{
		//���α׷� ���� ��θ� �����ͼ� ������ �о���� �ʿ䰡 �ִ� ����� �ش� ��ηκ��� ������ �о���Դϴ�.
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

	//���� ���� ��ü�� �� ���� ���� �ϴ� �Լ��Դϴ�.
	static void Release()
	{
		//������ �ʱ�ȭ�� �������� �ϴ����� �����մϴ�.
		//�ֳ��ϸ�, ���߿� �ʱ�ȭ �� ���� ���� �ʱ�ȭ �� ��� ���� ���Ӽ��� ���� �� �ֱ� �����Դϴ�.
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