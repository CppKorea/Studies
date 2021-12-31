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
	class Study_Schedule
	{
	public:
		//? ShowTaskList(?);
		//? AddTask(?);
		//? RemoveTask(?);
		//? ManageTask(?);
		
		//��Ÿ �Լ�

	private:
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>> m_taskList;
	};
}

#endif