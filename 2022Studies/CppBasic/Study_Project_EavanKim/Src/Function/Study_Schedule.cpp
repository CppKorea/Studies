#include "Grouping/headers_custom.h"

namespace Manager
{
	Study_Schedule::Study_Schedule()
		: m_status(ScheduleStatus::INITIALIZE)
	{
				
		//대기 모드로 정리합니다.
		m_status = ScheduleStatus::IDLE;
	}

	Study_Schedule::~Study_Schedule()
	{
	}

	int Study_Schedule::ShowTaskList(bool _Interrupt)
	{
		//작성 가능한 내용이 있는지 확인합니다.
		int Result = m_taskList.size();

		if (Result)
		{
			//데이터가 들어있다면 순회하면서 모든 데이터를 출력합니다.
			std::wstring Row;
			for (int Count = 0; Result > Count; ++Count)
			{
				m_taskList[Count].Get()->GetFullData(Row);
				std::wcout << Count << L" : " << Row << std::endl;
			}
		}
		else
		{
			//데이터가 없다면 비어있다는 경고를 출력합니다.
			std::wstring EmptyList;
			Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
			if (LocalizeMgr)
			{
				LocalizeMgr->GetLocalizeString(L"EMPTY_LIST", EmptyList);
				std::wcout << EmptyList << std::endl;
			}
		}

		//혹시 리스트를 출력하고 잠시 정지시키고 싶다면 Parameter를 TRUE로 만들면 정지합니다.
		if (_Interrupt)
		{
			std::wstring EndString;
			Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
			if (LocalizeMgr)
			{
				LocalizeMgr->GetLocalizeString(L"WAIT_LIST", EndString);
				std::wcout << EndString << std::endl;
			}
			std::wcin >> EndString;
		}

		return Result;
	}

	void Study_Schedule::AddTask(std::wstring _Task)
	{
		//새로운 ToDo를 만들어서 리스트에 추가합니다.
		Func_Object::Study_Task* newTask = new Func_Object::Study_Task(_Task);
		m_taskList.push_back(newTask);
	}

	void Study_Schedule::RemoveTask(int _Task)
	{
		//삭제하려는 대상 번호가 올바른지 최저한의 검증을 수행합니다.
		if ((_Task < 0) || (m_taskList.size() < _Task))
			return;

		//0번 위치의 Iterator를 구합니다.
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>>::iterator ListIter = m_taskList.begin();

		//입력된 숫자만큼 뒤로 넘깁니다.
		for (int Count = 0; _Task > Count; ++Count)
			++ListIter;

		//넘긴 대상으로 삭제를 수행합니다.
		m_taskList.erase(ListIter);
	}

	int Study_Schedule::TaskManage(Default::Study_Ptr<Func_Object::Study_Task>& _TaskPtr)
	{
		int Result = 0;

		//입출력 내용을 만들 컨테이너를 선언합니다.
		std::vector<Schedule_IO_Setup> OutPutSettings;

		//ToDo를 관리하는데 필요한 내용을 출력하고, 입력받을 내용을 결정합니다.
		//Localize에 저장되어있는 Manage 항목의 TITLE -> BODY -> END 순으로 출력을 지정합니다.
		//중간에 선택된 Task내용을 출력해서 어떤 내용이 선택되었는지 알려줍니다.
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE" });
		std::wstring GetTaskString;
		(_TaskPtr.Get())->GetFullData(GetTaskString);
		OutPutSettings.push_back({ GetTaskString });
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE0" });
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE1" });
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"END_MANAGE" });
		
		//화면을 한 번 지웁니다.
		Study_IO::ScreenClear();
	
		//세팅한 입출력 배열로 출력합니다.
		Result = ProcessIOSetupList(OutPutSettings);

		//동작한 결과가 정상이라면 다음 행동을 진행합니다.
		if (0 == Result)
		{
			//마지막 객체에 들어있는 입력값을 들고옵니다.
			int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

			//입출력 항목을 비워둡니다.
			OutPutSettings.clear();

			//입력된 값에 맞춰 입출력 항목을 새로 지정합니다.
			switch (InputValue)
			{
			case 0://상태 변경
				//ToDo 상태에 대한 변경을 진행합니다.
				//NONE -> PROGRESS -> DONE 순으로 진행을 가정하지만 변경은 마음대로 가능합니다.
				//해당 내용을 안내하는 내용과 선택되었던 ToDo 내용을 한 번 더 출력합니다.
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE_0" });
				OutPutSettings.push_back({ GetTaskString });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE_0_0" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE_0_1" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE_0_2" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"END_MANAGE_0" });
				Result = ProcessIOSetupList(OutPutSettings);
				if (0 == Result)
				{
					//마지막 객체에 들어있는 입력값을 들고옵니다.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;
					
					//Smart Pointer에서 객체 포인터에 접근한 뒤 값을 세팅합니다.
					//역시 Single Thread 전용 동작입니다.
					(_TaskPtr.Get())->SetStatus((Func_Object::TaskStatus)InputValue);
				}
				break;
			case 1://내용 수정
				//ToDo 상태에 대한 변경을 진행합니다.
				//NONE -> PROGRESS -> DONE 순으로 진행을 가정하지만 변경은 마음대로 가능합니다.
				//해당 내용을 안내하는 내용과 선택되었던 ToDo 내용을 한 번 더 출력합니다.
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE_1" });
				OutPutSettings.push_back({ GetTaskString });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_TEXT, L"END_MANAGE_1" });
				Result = ProcessIOSetupList(OutPutSettings);
				if (0 == Result)
				{
					//마지막 객체에 들어있는 입력값을 들고옵니다.
					std::wstring InputValue = OutPutSettings[OutPutSettings.size() - 1].input_text;

					//Smart Pointer에서 객체 포인터에 접근한 뒤 값을 세팅합니다.
					//역시 Single Thread 전용 동작입니다.
					(_TaskPtr.Get())->SetString(InputValue);
				}
				break;
			default://다른 입력은 그냥 끝납니다.
				break;
			}
		}

		return Result;
	}

	int Study_Schedule::ProcessIOSetupList(std::vector<Schedule_IO_Setup>& _list)
	{
		//들어온 리스트 사이즈만큼 순회할 준비 합니다.
		int MaxCount = _list.size();

		//순회를 시작합니다.
		for (int Count = 0; MaxCount > Count; ++Count)
		{
			//안에 들어있는 Type별 처리를 수행합니다.
			switch (_list[Count].type)
			{
			case Manager::Study_Schedule::IOType::OUT_TITLE: //제목은 =를 길게 붙여줍니다.
				Study_IO::ShowLine(_list[Count].text, 40, L'=');
				break;
			case Manager::Study_Schedule::IOType::IN_INT: //Int를 입력받는 동작입니다.
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_int);
				break;
			case Manager::Study_Schedule::IOType::IN_FLOAT: //Float을 입력받는 동작입니다.
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_float);
				break;
			case Manager::Study_Schedule::IOType::IN_TEXT: //문자열을 입력받는 동작입니다.
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_text);
				break;
			case Manager::Study_Schedule::IOType::IN_SUSPEND:
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_text);
				break;
			case Manager::Study_Schedule::IOType::SHOW_LIST: //리스트를 위에 출력하고 아래에서 동작하고 싶을때 쓰려고 정의되었습니다.
				ShowTaskList();
				break;
			default: //기본적으로 텍스트를 출력하는 동작을 수행합니다.
				Study_IO::ShowLine(_list[Count].text, 40);
				break;
			}
		}

		return 0;
	}

	void Study_Schedule::SetLoadedData(std::wstring& _loadedData)
	{
		//혹시 에러가 나면 상태를 변경하기 위한 매니저 포인터를 들고옵니다.
		Status* StatusMgr = Status::GetInstance();

		//상태 메니저가 초기화 되지 않았다면 게임 자체에 문제가 있다고 판단합니다.
		if (nullptr != StatusMgr)
		{
			//혹시 이미 문제가 있는 상태인지 확인합니다.
			PROGRAM_RUN_STATE LastStatus = StatusMgr->GetProgramRunState();
			if ((PROGRAM_RUN_STATE::EXCEPTION == LastStatus) || (PROGRAM_RUN_STATE::EXIT == LastStatus))
				return;

			//로드에 성공하면 현재 ToDo List를 지웁니다.
			m_taskList.clear();

			//마지막이 ;로 끝나는지 검사합니다.
			//그렇지 않다면 오작동의 위험이 있는 오염된 데이터로 취급합니다.
			if (L';' == _loadedData[_loadedData.length() - 1])
			{
				//파일로부터 가져온 문자열이 빌 때 까지 순회합니다.
				while (0 != _loadedData.length())
				{
					//; 위치를 찾아서 문자열 절단 기준점으로 삼습니다.
					size_t StringSize = _loadedData.find(L';');
					//혹시 문자열이 잘못되서 ;를 찾아내지 못하면 에러로 취급합니다.
					if (StringSize < _loadedData.length())
					{
						//문자열을 절단합니다.
						std::wstring SplitString(_loadedData.data(), StringSize, std::allocator<wchar_t>());
						//절단된 문자열을 삭제한 문자열로 갱신합니다.
						_loadedData = std::wstring(_loadedData, StringSize + 1, std::allocator<wchar_t>());

						//`위치를 찾아서 Key/Value로 절단할 기준점으로 삼습니다.
						size_t KeySize = SplitString.find(L'`');
						//혹시 문자열이 잘못되어서 `를 찾아내지 못하면 에러로 취급합니다.
						if (KeySize < SplitString.length())
						{
							//Key값을 잘라냅니다.
							std::wstring Key(SplitString.data(), KeySize, std::allocator<wchar_t>());
							//남은 문자열에서 `를 없애고 value를 가져옵니다.
							std::wstring Value(SplitString, KeySize + 1, std::allocator<wchar_t>());
							//두 자료를 모아 하나의 정보로 만들어 저장합니다.
							Func_Object::Study_Task* Task = new Func_Object::Study_Task(Key, Value);
							m_taskList.push_back(Task);
						}
						else
						{
							throw std::exception("File Is Corrupted!!!");
						}
					}
					else
					{
						throw std::exception("File Is Corrupted!!!");
					}
				}
			}
			else
			{
				throw std::exception("File Is Corrupted!!!");
			}
		}
	}

	bool Study_Schedule::CreateSaveData(std::wstring& _createdData)
	{
		bool Result = false;
		std::wstring Buffer;
		int MaxCount = m_taskList.size();

		for (int Count = 0; MaxCount > Count; ++Count)
		{
			(m_taskList[Count].Get())->CreateSaveData(Buffer);
			_createdData.append(Buffer);
			Result = true;
		}

		return Result;
	}

	int Study_Schedule::Run()
	{
		//루프에 진입 할 때마다 화면을 정리합니다.
		Study_IO::ScreenClear();

		//각종 매니저에 대한 포인터를 얻어옵니다.
		Status* StatusMgr = Status::GetInstance();
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		
		//함수 안에서 사용할 객체를 정의합니다.
		std::vector<Schedule_IO_Setup> OutPutSettings;

		//매니저가 올바르게 존재하는 경우에만 동작합니다.
		if (StatusMgr && LocalizeMgr)
		{
			//상태값에 따라 출력과 입력을 받도록 합니다.
			switch (m_status)
			{
			case ScheduleStatus::INITIALIZE:
				//Run에 들어왔는데 Initialize면 오류로 인해 IDLE로 못 돌아간 것이니 문제상황입니다.
				StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				break;
			case ScheduleStatus::IDLE://기본 메뉴를 출력하고 처리하는 분기입니다.
			{
				//기본 출력 내용을 세팅합니다.
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_IDLE" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE0" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE1" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE2" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE3" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE4" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE5" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE6" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"INPUT_IDLE" });

				//내용을 출력합니다.
				//올바르게 동작하지 않는다면 프로그램을 종료합니다.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//마지막 칸에 있는 입력된 내용을 가져옵니다.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

					//범위를 벗어나는 동작인지 확인합니다.
					if ((0 < InputValue) && (InputValue < (int)ScheduleStatus::END))
					{
						switch (InputValue)//값으로 분기를 수행합니다.
						{
						case 1://리스트를 한 번 출력하고 입력 대기 후 무언가 입력되면 다시 기본 화면으로 돌아갑니다.
							ShowTaskList(true);
							m_status = ScheduleStatus::IDLE;
							break;
						case 2://ToDo를 추가합니다.
							m_status = ScheduleStatus::ADD;
							break;
						case 3://ToDo를 삭제합니다.
							m_status = ScheduleStatus::REMOVE;
							break;
						case 4://ToDo를 편집합니다.
							m_status = ScheduleStatus::MANAGE;
							break;
						case 5://저장합니다
							m_status = ScheduleStatus::SAVE;
							break;
						case 6://불러옵니다
							m_status = ScheduleStatus::LOAD;
							break;
						}
					}
					else
					{
						//잘못된 입력은 종료로 판정합니다.
						StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXIT);
						StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::EXIT);
						return -1;
					}
				}
				else
				{
					//입출력 에러로 판정합니다.
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
			}
				break;
			case ScheduleStatus::ADD://ToDo를 추가하고 다시 IDLE로 돌아가는 분기입니다.
			{
				//기본 출력 내용을 세팅합니다.
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_ADD"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_TEXT, L"INPUT_ADD"));

				//내용을 출력합니다.
				//올바른 입력이 아니라면 IDLE로 돌아가고, 오작동시에는 프로그램을 종료합니다.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//마지막 칸에 있는 입력된 내용을 가져옵니다.
					std::wstring InputValue = OutPutSettings[OutPutSettings.size() - 1].input_text;

					//입력된 값으로 ToDo를 추가하는 동작을 수행합니다.
					AddTask(InputValue);
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}

				//IDLE로 돌아갑니다.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::REMOVE:
			{
				//기본 출력 내용을 세팅합니다.
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_REMOVE"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_REMOVE"));

				//내용을 출력합니다.
				//올바른 입력이 아니라면 IDLE로 돌아가고, 오작동시에는 프로그램을 종료합니다.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//마지막 칸에 있는 입력된 내용을 가져옵니다.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

					//입력된 값으로 ToDo를 삭제하는 동작을 수행합니다.
					RemoveTask(InputValue);
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}

				//IDLE로 돌아갑니다.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::MANAGE:
			{
				//기본 출력 내용을 세팅합니다.
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_MANAGE"));

				//내용을 출력합니다.
				//올바른 입력이 아니라면 IDLE로 돌아가고, 오작동시에는 프로그램을 종료합니다.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//마지막 칸에 있는 입력된 내용을 가져옵니다.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

					//입력된 값이 가리키는 ToDo를 편집하는 함수로 넘겨줍니다.
					TaskManage(m_taskList[InputValue]);
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}

				//IDLE로 돌아갑니다.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::SAVE:
			{
				TCHAR programpathBuffer[_MAX_PATH];
				GetCurrentDirectory(_MAX_PATH, programpathBuffer);

				std::wstring programpath(programpathBuffer);
				std::wstring saveData;
				if (CreateSaveData(saveData))
				{
					Study_IO::DataSave(programpath + L"\\ToDoSaveFile", saveData);
				}

				//IDLE로 돌아갑니다.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::LOAD:
			{
				//프로그램 실행 경로를 가져와서 파일을 읽어들일 필요가 있는 대상은 해당 경로로부터 정보를 읽어들입니다.
				TCHAR programpathBuffer[_MAX_PATH];
				GetCurrentDirectory(_MAX_PATH, programpathBuffer);

				std::wstring programpath(programpathBuffer);
				std::wstring loadedData;

				Study_IO::DataLoad(programpath + L"\\ToDoSaveFile", loadedData);

				SetLoadedData(loadedData);

				//IDLE로 돌아갑니다.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			default:

				//IDLE로 돌아갑니다.
				m_status = ScheduleStatus::IDLE;
				break;
			}
		}

		return 0;
	}
}
