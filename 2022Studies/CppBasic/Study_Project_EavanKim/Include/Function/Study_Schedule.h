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
		explicit Study_Schedule();
		~Study_Schedule();

		int ShowTaskList();
		bool AddTask(std::wstring _Task);
		bool RemoveTask(int _Task);
		int TaskManage(TaskStatus _Status);
		
		int Run();

	private:
		ScheduleStatus m_status;
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>> m_taskList;
	};
}

#endif