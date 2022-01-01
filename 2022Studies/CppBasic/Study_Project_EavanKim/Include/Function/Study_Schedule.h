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