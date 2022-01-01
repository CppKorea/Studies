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
			std::wstring EmptyList;
			Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
			if (LocalizeMgr)
			{
				LocalizeMgr->GetLocalizeString(L"EMPTY_LIST", EmptyList);
				std::wcout << EmptyList << std::endl;
			}
		}

		std::wstring EndString;
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		if (LocalizeMgr)
		{
			LocalizeMgr->GetLocalizeString(L"WAIT_LIST", EndString);
			std::wcout << EndString << std::endl;
		}
		std::wcin >> EndString;

		return Result;
	}
	bool Study_Schedule::AddTask(std::wstring _Task)
	{
		bool Result = false;

		Func_Object::Study_Task* newTask = new Func_Object::Study_Task();
		m_taskList.push_back(newTask);
		Result = true;

		return Result;
	}
	bool Study_Schedule::RemoveTask(int _Task)
	{
		bool Result = false;

		if ((_Task < 0) || (m_taskList.size() < _Task))
			return Result;



		return Result;
	}
	int Study_Schedule::TaskManage(TaskStatus _Status)
	{
		return 0;
	}

	int Study_Schedule::ProcessIOSetupList(std::vector<Schedule_IO_Setup>& _list)
	{
		int MaxCount = _list.size();
		for (int Count = 0; MaxCount > Count; ++Count)
		{
			switch (_list[Count].type)
			{
			case Manager::Study_Schedule::IOType::OUT_TITLE:
				Study_IO::ShowLine(_list[Count].text, 40, L'=');
				break;
			case Manager::Study_Schedule::IOType::IN_INT:
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_int);
				break;
			case Manager::Study_Schedule::IOType::IN_FLOAT:
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_float);
				break;
			case Manager::Study_Schedule::IOType::IN_TEXT:
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_text);
				break;
			default:
				Study_IO::ShowLine(_list[Count].text, 40);
				break;
			}
		}

		return 0;
	}

	int Study_Schedule::Run()
	{
		Study_IO::ScreenClear();
		Status* StatusMgr = Status::GetInstance();
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		
		std::wstring Buffer;
		std::vector<Schedule_IO_Setup> OutPutSettings;

		if (StatusMgr && LocalizeMgr)
		{
			//상태값에 따라 출력과 입력을 받도록 합니다.
			switch (m_status)
			{
			case ScheduleStatus::INITIALIZE:
				break;
			case ScheduleStatus::IDLE:
			{
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_IDLE" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE0" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE1" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE2" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE3" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE4" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"INPUT_IDLE" });
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;
					if ((0 < InputValue) && (InputValue < (int)ScheduleStatus::END))
					{
						switch (InputValue)
						{
						case 1:
							ShowTaskList();
							m_status = ScheduleStatus::IDLE;
							break;
						case 2:
							m_status = ScheduleStatus::ADD;
							break;
						case 3:
							m_status = ScheduleStatus::REMOVE;
							break;
						case 4:
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
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
			}
				break;
			case ScheduleStatus::ADD:
			{
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_ADD"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_ADD"));
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					std::wstring InputValue = OutPutSettings[2].input_text;
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::REMOVE:
			{
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_REMOVE"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_REMOVE"));
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					std::wstring InputValue = OutPutSettings[2].input_text;
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::MANAGE:
			{
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_MANAGE"));
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					std::wstring InputValue = OutPutSettings[2].input_text;
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
				m_status = ScheduleStatus::IDLE;
			}
				break;
			default:
				m_status = ScheduleStatus::IDLE;
				break;
			}
		}

		return 0;
	}
}
