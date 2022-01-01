#include "Grouping/headers_custom.h"

namespace Manager
{
	Study_Schedule::Study_Schedule()
		: m_status(ScheduleStatus::INITIALIZE)
	{
		

		m_status = ScheduleStatus::IDLE;
	}
	Study_Schedule::~Study_Schedule()
	{
	}
	int Study_Schedule::ShowTaskList()
	{
		int Result = m_taskList.size();

		if (Result)
		{
			for (int Count = 0; Result > Count; ++Count)
			{
				std::wcout << Count << L" : " << m_taskList[Count].Get()->GetShowData() << std::endl;
			}
		}
		else
		{

		}

		return Result;
	}
	bool Study_Schedule::AddTask(std::wstring _Task)
	{
		bool Result = false;

		return Result;
	}
	bool Study_Schedule::RemoveTask(int _Task)
	{
		bool Result = false;

		return Result;
	}
	int Study_Schedule::TaskManage(TaskStatus _Status)
	{
		return 0;
	}
	int Study_Schedule::Run()
	{
		Status* StatusMgr = Status::GetInstance();
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();

		std::wstring Title;
		std::wstring Body;
		std::wstring Body0;
		std::wstring Body1;
		std::wstring Body2;
		std::wstring Body3;
		std::wstring End;
		int InputInteger;
		std::wstring InputString;
		float InputFloat;

		if (StatusMgr && LocalizeMgr)
		{
			switch (m_status)
			{
			case ScheduleStatus::INITIALIZE:
				break;
			case ScheduleStatus::IDLE:
				LocalizeMgr->GetLocalizeString(L"TITLE_IDLE", Title);
				LocalizeMgr->GetLocalizeString(L"BODY_IDLE0", Body0);
				LocalizeMgr->GetLocalizeString(L"BODY_IDLE1", Body1);
				LocalizeMgr->GetLocalizeString(L"BODY_IDLE2", Body2);
				LocalizeMgr->GetLocalizeString(L"BODY_IDLE3", Body3);
				LocalizeMgr->GetLocalizeString(L"END_IDLE", End);
				Study_IO::ShowLine(Title, 40, L'=');
				Study_IO::ShowLine(Body0, 40);
				Study_IO::ShowLine(Body1, 40);
				Study_IO::ShowLine(Body2, 40);
				Study_IO::ShowLine(Body3, 40);
				Study_IO::WaitInput(End, InputInteger);
				if ((0 < InputInteger) && (InputInteger < (int)ScheduleStatus::END))
				{
					switch (InputInteger)
					{
					case 1:
						m_status = ScheduleStatus::ADD;
						break;
					case 2:
						m_status = ScheduleStatus::REMOVE;
						break;
					case 3:
						m_status = ScheduleStatus::MANAGE;
						break;
					}
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
				break;
			case ScheduleStatus::ADD:
				LocalizeMgr->GetLocalizeString(L"TITLE_ADD", Title);
				LocalizeMgr->GetLocalizeString(L"BODY_ADD", Body);
				LocalizeMgr->GetLocalizeString(L"END_ADD", End);
				Study_IO::ShowLine(Title, 40, L'=');
				Study_IO::ShowLine(Body, 40);
				Study_IO::WaitInput(End, InputString);
				break;
			case ScheduleStatus::REMOVE:
				LocalizeMgr->GetLocalizeString(L"TITLE_REMOVE", Title);
				LocalizeMgr->GetLocalizeString(L"BODY_REMOVE", Body);
				LocalizeMgr->GetLocalizeString(L"END_REMOVE", End);
				Study_IO::ShowLine(Title, 40, L'=');
				Study_IO::ShowLine(Body, 40);
				Study_IO::WaitInput(End, InputInteger);
				if ((-1 < InputInteger) && (InputInteger < m_taskList.size()))
				{

				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
				break;
			case ScheduleStatus::MANAGE:
				LocalizeMgr->GetLocalizeString(L"TITLE_MANAGE", Title);
				LocalizeMgr->GetLocalizeString(L"BODY_MANAGE", Body);
				LocalizeMgr->GetLocalizeString(L"END_MANAGE", End);
				Study_IO::ShowLine(Title, 40, L'=');
				Study_IO::ShowLine(Body, 40);
				Study_IO::WaitInput(End, InputInteger);
				if ((-1 < InputInteger) && (InputInteger < (int)TaskStatus::END))
				{

				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
				break;
			default:
				break;
			}
		}

		return 0;
	}
}
