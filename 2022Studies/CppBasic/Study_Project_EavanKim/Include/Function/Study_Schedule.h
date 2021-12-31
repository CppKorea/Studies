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
	class Study_Schedule
	{
	public:
		//? ShowTaskList(?);
		//? AddTask(?);
		//? RemoveTask(?);
		//? ManageTask(?);
		
		//기타 함수

	private:
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>> m_taskList;
	};
}

#endif