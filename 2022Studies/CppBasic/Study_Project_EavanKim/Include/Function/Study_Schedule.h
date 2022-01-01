#ifndef SCHEDULE_H__
#define SCHEDULE_H__

#include "Study_Task.h"

/*
* 
* (※경고※) 무근본 자기류 코드 작성법이 사용되었습니다.
* 코드 작성자가 실수하는 부분들을 막으려는 개인적인 작성법이 사용되어 있습니다.
* 코드 작성에 대한 방법은 참조하시지 마시고 이런 생각이 있구나 정도만 참고하여 주십시오.
* 
* Schedule Manager
* 
*/

namespace Manager
{
	enum class TaskStatus
	{
		NONE
		, PROGRASS
		, DONE
		, END
	};

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

		int ShowTaskList();
		bool AddTask(std::wstring _Task);
		bool RemoveTask(int _Task);
		int TaskManage(TaskStatus _Status);
		int ProcessIOSetupList(std::vector<Schedule_IO_Setup>& _list);

		int Run();

	private:
		ScheduleStatus m_status;
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>> m_taskList;
	};
}

#endif