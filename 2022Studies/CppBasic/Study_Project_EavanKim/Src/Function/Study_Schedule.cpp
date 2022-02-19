#include "Grouping/headers_custom.h"

namespace Manager
{
	Study_Schedule::Study_Schedule()
		: m_status(ScheduleStatus::INITIALIZE)
	{
				
		//��� ���� �����մϴ�.
		m_status = ScheduleStatus::IDLE;
	}

	Study_Schedule::~Study_Schedule()
	{
	}

	int Study_Schedule::ShowTaskList(bool _Interrupt)
	{
		//�ۼ� ������ ������ �ִ��� Ȯ���մϴ�.
		int Result = m_taskList.size();

		if (Result)
		{
			//�����Ͱ� ����ִٸ� ��ȸ�ϸ鼭 ��� �����͸� ����մϴ�.
			std::wstring Row;
			for (int Count = 0; Result > Count; ++Count)
			{
				m_taskList[Count].Get()->GetFullData(Row);
				std::wcout << Count << L" : " << Row << std::endl;
			}
		}
		else
		{
			//�����Ͱ� ���ٸ� ����ִٴ� ��� ����մϴ�.
			std::wstring EmptyList;
			Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
			if (LocalizeMgr)
			{
				LocalizeMgr->GetLocalizeString(L"EMPTY_LIST", EmptyList);
				std::wcout << EmptyList << std::endl;
			}
		}

		//Ȥ�� ����Ʈ�� ����ϰ� ��� ������Ű�� �ʹٸ� Parameter�� TRUE�� ����� �����մϴ�.
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
		//���ο� ToDo�� ���� ����Ʈ�� �߰��մϴ�.
		Func_Object::Study_Task* newTask = new Func_Object::Study_Task(_Task);
		m_taskList.push_back(newTask);
	}

	void Study_Schedule::RemoveTask(int _Task)
	{
		//�����Ϸ��� ��� ��ȣ�� �ùٸ��� �������� ������ �����մϴ�.
		if ((_Task < 0) || (m_taskList.size() < _Task))
			return;

		//0�� ��ġ�� Iterator�� ���մϴ�.
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>>::iterator ListIter = m_taskList.begin();

		//�Էµ� ���ڸ�ŭ �ڷ� �ѱ�ϴ�.
		for (int Count = 0; _Task > Count; ++Count)
			++ListIter;

		//�ѱ� ������� ������ �����մϴ�.
		m_taskList.erase(ListIter);
	}

	int Study_Schedule::TaskManage(Default::Study_Ptr<Func_Object::Study_Task>& _TaskPtr)
	{
		int Result = 0;

		//����� ������ ���� �����̳ʸ� �����մϴ�.
		std::vector<Schedule_IO_Setup> OutPutSettings;

		//ToDo�� �����ϴµ� �ʿ��� ������ ����ϰ�, �Է¹��� ������ �����մϴ�.
		//Localize�� ����Ǿ��ִ� Manage �׸��� TITLE -> BODY -> END ������ ����� �����մϴ�.
		//�߰��� ���õ� Task������ ����ؼ� � ������ ���õǾ����� �˷��ݴϴ�.
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE" });
		std::wstring GetTaskString;
		(_TaskPtr.Get())->GetFullData(GetTaskString);
		OutPutSettings.push_back({ GetTaskString });
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE0" });
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE1" });
		OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"END_MANAGE" });
		
		//ȭ���� �� �� ����ϴ�.
		Study_IO::ScreenClear();
	
		//������ ����� �迭�� ����մϴ�.
		Result = ProcessIOSetupList(OutPutSettings);

		//������ ����� �����̶�� ���� �ൿ�� �����մϴ�.
		if (0 == Result)
		{
			//������ ��ü�� ����ִ� �Է°��� ���ɴϴ�.
			int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

			//����� �׸��� ����Ӵϴ�.
			OutPutSettings.clear();

			//�Էµ� ���� ���� ����� �׸��� ���� �����մϴ�.
			switch (InputValue)
			{
			case 0://���� ����
				//ToDo ���¿� ���� ������ �����մϴ�.
				//NONE -> PROGRESS -> DONE ������ ������ ���������� ������ ������� �����մϴ�.
				//�ش� ������ �ȳ��ϴ� ����� ���õǾ��� ToDo ������ �� �� �� ����մϴ�.
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE_0" });
				OutPutSettings.push_back({ GetTaskString });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE_0_0" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE_0_1" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_MANAGE_0_2" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"END_MANAGE_0" });
				Result = ProcessIOSetupList(OutPutSettings);
				if (0 == Result)
				{
					//������ ��ü�� ����ִ� �Է°��� ���ɴϴ�.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;
					
					//Smart Pointer���� ��ü �����Ϳ� ������ �� ���� �����մϴ�.
					//���� Single Thread ���� �����Դϴ�.
					(_TaskPtr.Get())->SetStatus((Func_Object::TaskStatus)InputValue);
				}
				break;
			case 1://���� ����
				//ToDo ���¿� ���� ������ �����մϴ�.
				//NONE -> PROGRESS -> DONE ������ ������ ���������� ������ ������� �����մϴ�.
				//�ش� ������ �ȳ��ϴ� ����� ���õǾ��� ToDo ������ �� �� �� ����մϴ�.
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE_1" });
				OutPutSettings.push_back({ GetTaskString });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_TEXT, L"END_MANAGE_1" });
				Result = ProcessIOSetupList(OutPutSettings);
				if (0 == Result)
				{
					//������ ��ü�� ����ִ� �Է°��� ���ɴϴ�.
					std::wstring InputValue = OutPutSettings[OutPutSettings.size() - 1].input_text;

					//Smart Pointer���� ��ü �����Ϳ� ������ �� ���� �����մϴ�.
					//���� Single Thread ���� �����Դϴ�.
					(_TaskPtr.Get())->SetString(InputValue);
				}
				break;
			default://�ٸ� �Է��� �׳� �����ϴ�.
				break;
			}
		}

		return Result;
	}

	int Study_Schedule::ProcessIOSetupList(std::vector<Schedule_IO_Setup>& _list)
	{
		//���� ����Ʈ �����ŭ ��ȸ�� �غ� �մϴ�.
		int MaxCount = _list.size();

		//��ȸ�� �����մϴ�.
		for (int Count = 0; MaxCount > Count; ++Count)
		{
			//�ȿ� ����ִ� Type�� ó���� �����մϴ�.
			switch (_list[Count].type)
			{
			case Manager::Study_Schedule::IOType::OUT_TITLE: //������ =�� ��� �ٿ��ݴϴ�.
				Study_IO::ShowLine(_list[Count].text, 40, L'=');
				break;
			case Manager::Study_Schedule::IOType::IN_INT: //Int�� �Է¹޴� �����Դϴ�.
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_int);
				break;
			case Manager::Study_Schedule::IOType::IN_FLOAT: //Float�� �Է¹޴� �����Դϴ�.
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_float);
				break;
			case Manager::Study_Schedule::IOType::IN_TEXT: //���ڿ��� �Է¹޴� �����Դϴ�.
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_text);
				break;
			case Manager::Study_Schedule::IOType::IN_SUSPEND:
				Study_IO::WaitInput(_list[Count].text, _list[Count].input_text);
				break;
			case Manager::Study_Schedule::IOType::SHOW_LIST: //����Ʈ�� ���� ����ϰ� �Ʒ����� �����ϰ� ������ ������ ���ǵǾ����ϴ�.
				ShowTaskList();
				break;
			default: //�⺻������ �ؽ�Ʈ�� ����ϴ� ������ �����մϴ�.
				Study_IO::ShowLine(_list[Count].text, 40);
				break;
			}
		}

		return 0;
	}

	void Study_Schedule::SetLoadedData(std::wstring& _loadedData)
	{
		//Ȥ�� ������ ���� ���¸� �����ϱ� ���� �Ŵ��� �����͸� ���ɴϴ�.
		Status* StatusMgr = Status::GetInstance();

		//���� �޴����� �ʱ�ȭ ���� �ʾҴٸ� ���� ��ü�� ������ �ִٰ� �Ǵ��մϴ�.
		if (nullptr != StatusMgr)
		{
			//Ȥ�� �̹� ������ �ִ� �������� Ȯ���մϴ�.
			PROGRAM_RUN_STATE LastStatus = StatusMgr->GetProgramRunState();
			if ((PROGRAM_RUN_STATE::EXCEPTION == LastStatus) || (PROGRAM_RUN_STATE::EXIT == LastStatus))
				return;

			//�ε忡 �����ϸ� ���� ToDo List�� ����ϴ�.
			m_taskList.clear();

			//�������� ;�� �������� �˻��մϴ�.
			//�׷��� �ʴٸ� ���۵��� ������ �ִ� ������ �����ͷ� ����մϴ�.
			if (L';' == _loadedData[_loadedData.length() - 1])
			{
				//���Ϸκ��� ������ ���ڿ��� �� �� ���� ��ȸ�մϴ�.
				while (0 != _loadedData.length())
				{
					//; ��ġ�� ã�Ƽ� ���ڿ� ���� ���������� ����ϴ�.
					size_t StringSize = _loadedData.find(L';');
					//Ȥ�� ���ڿ��� �߸��Ǽ� ;�� ã�Ƴ��� ���ϸ� ������ ����մϴ�.
					if (StringSize < _loadedData.length())
					{
						//���ڿ��� �����մϴ�.
						std::wstring SplitString(_loadedData.data(), StringSize, std::allocator<wchar_t>());
						//���ܵ� ���ڿ��� ������ ���ڿ��� �����մϴ�.
						_loadedData = std::wstring(_loadedData, StringSize + 1, std::allocator<wchar_t>());

						//`��ġ�� ã�Ƽ� Key/Value�� ������ ���������� ����ϴ�.
						size_t KeySize = SplitString.find(L'`');
						//Ȥ�� ���ڿ��� �߸��Ǿ `�� ã�Ƴ��� ���ϸ� ������ ����մϴ�.
						if (KeySize < SplitString.length())
						{
							//Key���� �߶���ϴ�.
							std::wstring Key(SplitString.data(), KeySize, std::allocator<wchar_t>());
							//���� ���ڿ����� `�� ���ְ� value�� �����ɴϴ�.
							std::wstring Value(SplitString, KeySize + 1, std::allocator<wchar_t>());
							//�� �ڷḦ ��� �ϳ��� ������ ����� �����մϴ�.
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
		//������ ���� �� ������ ȭ���� �����մϴ�.
		Study_IO::ScreenClear();

		//���� �Ŵ����� ���� �����͸� ���ɴϴ�.
		Status* StatusMgr = Status::GetInstance();
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		
		//�Լ� �ȿ��� ����� ��ü�� �����մϴ�.
		std::vector<Schedule_IO_Setup> OutPutSettings;

		//�Ŵ����� �ùٸ��� �����ϴ� ��쿡�� �����մϴ�.
		if (StatusMgr && LocalizeMgr)
		{
			//���°��� ���� ��°� �Է��� �޵��� �մϴ�.
			switch (m_status)
			{
			case ScheduleStatus::INITIALIZE:
				//Run�� ���Դµ� Initialize�� ������ ���� IDLE�� �� ���ư� ���̴� ������Ȳ�Դϴ�.
				StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				break;
			case ScheduleStatus::IDLE://�⺻ �޴��� ����ϰ� ó���ϴ� �б��Դϴ�.
			{
				//�⺻ ��� ������ �����մϴ�.
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_IDLE" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE0" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE1" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE2" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE3" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE4" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE5" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::OUT_TEXT, L"BODY_IDLE6" });
				OutPutSettings.push_back({ Manager::Study_Schedule::IOType::IN_INT, L"INPUT_IDLE" });

				//������ ����մϴ�.
				//�ùٸ��� �������� �ʴ´ٸ� ���α׷��� �����մϴ�.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//������ ĭ�� �ִ� �Էµ� ������ �����ɴϴ�.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

					//������ ����� �������� Ȯ���մϴ�.
					if ((0 < InputValue) && (InputValue < (int)ScheduleStatus::END))
					{
						switch (InputValue)//������ �б⸦ �����մϴ�.
						{
						case 1://����Ʈ�� �� �� ����ϰ� �Է� ��� �� ���� �ԷµǸ� �ٽ� �⺻ ȭ������ ���ư��ϴ�.
							ShowTaskList(true);
							m_status = ScheduleStatus::IDLE;
							break;
						case 2://ToDo�� �߰��մϴ�.
							m_status = ScheduleStatus::ADD;
							break;
						case 3://ToDo�� �����մϴ�.
							m_status = ScheduleStatus::REMOVE;
							break;
						case 4://ToDo�� �����մϴ�.
							m_status = ScheduleStatus::MANAGE;
							break;
						case 5://�����մϴ�
							m_status = ScheduleStatus::SAVE;
							break;
						case 6://�ҷ��ɴϴ�
							m_status = ScheduleStatus::LOAD;
							break;
						}
					}
					else
					{
						//�߸��� �Է��� ����� �����մϴ�.
						StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXIT);
						StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::EXIT);
						return -1;
					}
				}
				else
				{
					//����� ������ �����մϴ�.
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}
			}
				break;
			case ScheduleStatus::ADD://ToDo�� �߰��ϰ� �ٽ� IDLE�� ���ư��� �б��Դϴ�.
			{
				//�⺻ ��� ������ �����մϴ�.
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_ADD"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_TEXT, L"INPUT_ADD"));

				//������ ����մϴ�.
				//�ùٸ� �Է��� �ƴ϶�� IDLE�� ���ư���, ���۵��ÿ��� ���α׷��� �����մϴ�.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//������ ĭ�� �ִ� �Էµ� ������ �����ɴϴ�.
					std::wstring InputValue = OutPutSettings[OutPutSettings.size() - 1].input_text;

					//�Էµ� ������ ToDo�� �߰��ϴ� ������ �����մϴ�.
					AddTask(InputValue);
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}

				//IDLE�� ���ư��ϴ�.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::REMOVE:
			{
				//�⺻ ��� ������ �����մϴ�.
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_REMOVE"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_REMOVE"));

				//������ ����մϴ�.
				//�ùٸ� �Է��� �ƴ϶�� IDLE�� ���ư���, ���۵��ÿ��� ���α׷��� �����մϴ�.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//������ ĭ�� �ִ� �Էµ� ������ �����ɴϴ�.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

					//�Էµ� ������ ToDo�� �����ϴ� ������ �����մϴ�.
					RemoveTask(InputValue);
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}

				//IDLE�� ���ư��ϴ�.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::MANAGE:
			{
				//�⺻ ��� ������ �����մϴ�.
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::OUT_TITLE, L"TITLE_MANAGE"));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::SHOW_LIST));
				OutPutSettings.push_back(Schedule_IO_Setup(Manager::Study_Schedule::IOType::IN_INT, L"INPUT_MANAGE"));

				//������ ����մϴ�.
				//�ùٸ� �Է��� �ƴ϶�� IDLE�� ���ư���, ���۵��ÿ��� ���α׷��� �����մϴ�.
				if (0 == ProcessIOSetupList(OutPutSettings))
				{
					//������ ĭ�� �ִ� �Էµ� ������ �����ɴϴ�.
					int InputValue = OutPutSettings[OutPutSettings.size() - 1].input_int;

					//�Էµ� ���� ����Ű�� ToDo�� �����ϴ� �Լ��� �Ѱ��ݴϴ�.
					TaskManage(m_taskList[InputValue]);
				}
				else
				{
					StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
					StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::CONSOLIN);
					return -1;
				}

				//IDLE�� ���ư��ϴ�.
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

				//IDLE�� ���ư��ϴ�.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			case ScheduleStatus::LOAD:
			{
				//���α׷� ���� ��θ� �����ͼ� ������ �о���� �ʿ䰡 �ִ� ����� �ش� ��ηκ��� ������ �о���Դϴ�.
				TCHAR programpathBuffer[_MAX_PATH];
				GetCurrentDirectory(_MAX_PATH, programpathBuffer);

				std::wstring programpath(programpathBuffer);
				std::wstring loadedData;

				Study_IO::DataLoad(programpath + L"\\ToDoSaveFile", loadedData);

				SetLoadedData(loadedData);

				//IDLE�� ���ư��ϴ�.
				m_status = ScheduleStatus::IDLE;
			}
				break;
			default:

				//IDLE�� ���ư��ϴ�.
				m_status = ScheduleStatus::IDLE;
				break;
			}
		}

		return 0;
	}
}
