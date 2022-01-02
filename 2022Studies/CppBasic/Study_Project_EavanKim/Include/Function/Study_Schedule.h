#ifndef SCHEDULE_H__
#define SCHEDULE_H__

#include "Study_Task.h"

/*
* 
* (�ذ���) ���ٺ� �ڱ�� �ڵ� �ۼ����� ���Ǿ����ϴ�.
* �ڵ� �ۼ��ڰ� �Ǽ��ϴ� �κе��� �������� �������� �ۼ����� ���Ǿ� �ֽ��ϴ�.
* �ڵ� �ۼ��� ���� ����� �����Ͻ��� ���ð� �̷� ������ �ֱ��� ������ �����Ͽ� �ֽʽÿ�.
* 
* Schedule Manager
* ToDo�� 1:1�� ��Ī�Ǵ� Task ��ü�� �����ϴ� ��ü�Դϴ�.
* 
*/

namespace Manager
{

	enum class ScheduleStatus
	{
		INITIALIZE
		, IDLE
		, ADD
		, REMOVE
		, MANAGE
		, END
	};

	class Study_Schedule
	{
	public:
		enum class IOType
		{
			OUT_TEXT
			, OUT_TITLE
			, OUT_CUSTOMTEXT
			, IN_INT
			, IN_FLOAT
			, IN_TEXT
			, SHOW_LIST
		};

		struct Schedule_IO_Setup
		{
			Schedule_IO_Setup(IOType _type)
				: type(_type)
				, valied(true)
				, textkey(L"")
				, text(L"")
				, input_int(0)
				, input_float(0)
				, input_text(L"")
			{
			}

			Schedule_IO_Setup(wchar_t* _Text)
				: type(IOType::OUT_CUSTOMTEXT)
				, valied(true)
				, textkey(L"")
				, text(_Text)
				, input_int(0)
				, input_float(0)
				, input_text(L"")
			{
			}

			Schedule_IO_Setup(std::wstring _Text)
				: type(IOType::OUT_CUSTOMTEXT)
				, valied(true)
				, textkey(L"")
				, text(_Text)
				, input_int(0)
				, input_float(0)
				, input_text(L"")
			{
			}

			Schedule_IO_Setup(IOType _type, wchar_t* _TextKey)
				: type(_type)
				, valied(false)
				, textkey(_TextKey)
				, input_int(0)
				, input_float(0)
				, input_text(L"")
			{
				Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
				if (LocalizeMgr)
					valied = LocalizeMgr->GetLocalizeString(textkey, text);

			}

			Schedule_IO_Setup(IOType _type, std::wstring _TextKey)
				: type(_type)
				, valied(false)
				, textkey(_TextKey)
				, input_int(0)
				, input_float(0)
				, input_text(L"")
			{
				Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
				if (LocalizeMgr)
					valied = LocalizeMgr->GetLocalizeString(textkey, text);
			}

			Schedule_IO_Setup(const Schedule_IO_Setup& _Copy)
				: type(_Copy.type)
				, valied(_Copy.valied)
				, textkey(_Copy.textkey)
				, text(_Copy.text)
				, input_int(_Copy.input_int)
				, input_float(_Copy.input_float)
				, input_text(_Copy.input_text)
			{
			}

			Schedule_IO_Setup(const Schedule_IO_Setup&& _Copy)
				: type(_Copy.type)
				, valied(_Copy.valied)
				, textkey(_Copy.textkey)
				, text(_Copy.text)
				, input_int(_Copy.input_int)
				, input_float(_Copy.input_float)
				, input_text(_Copy.input_text)
			{
			}

			IOType type;
			bool valied;
			std::wstring textkey;
			std::wstring text;
			int input_int;
			float input_float;
			std::wstring input_text;
		};

		explicit Study_Schedule();
		~Study_Schedule();

		//��ü ����Ʈ�� ����մϴ�.
		//_Interrupt�� true�� ���߸� �Է��� ������ �� ���� ����Ʈ ��¿� �ӹ����ϴ�.
		int ShowTaskList(bool _Interrupt = false);

		//ToDo List�� �Է¹��� ���ڸ� �Է��� ���ο� Task�� �����Ѵ�.
		void AddTask(std::wstring _Task);
		
		//ToDo List���� ����� �ٷ� �����մϴ�.
		void RemoveTask(int _Task);

		//Task Setup Process.
		//�ȿ��� ProcessIOSetupList�� �����ϸ鼭 �Է��� �޾� ó��
		int TaskManage(Default::Study_Ptr<Func_Object::Study_Task>& _TaskPtr);

		//����� ���� ó�� ���� ����
		int ProcessIOSetupList(std::vector<Schedule_IO_Setup>& _list);
		
		//���� ���� ����
		int Run();

	private:
		ScheduleStatus m_status;
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>> m_taskList;
	};
}

#endif