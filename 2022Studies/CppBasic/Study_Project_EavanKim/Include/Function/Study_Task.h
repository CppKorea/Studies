#ifndef	STUDY_TASK_H__
#define STUDY_TASK_H__

/*
*
* (※경고※) 무근본 자기류 코드 작성법이 사용되었습니다.
* 코드 작성자가 실수하는 부분들을 막으려는 개인적인 작성법이 사용되어 있습니다.
* 코드 작성에 대한 방법은 참조하시지 마시고 이런 생각이 있구나 정도만 참고하여 주십시오.
*
* Study_Task
* ToDo의 한 행을 구성하는 자료의 집합에 대한 객체입니다.
*
*/

namespace Manager
{
	namespace Func_Object
	{
		//자료 중 하나인 ToDo 상태입니다.
		enum class TaskStatus
		{
			NONE
			, PROGRASS
			, DONE
			, END
		};

		//자료의 집합인 정보는 객체로 다루는 편이 개인적인 습관입니다.
		class Study_Task : public Default::Study_Object
		{
		public:
			//생성할 때 초기값으로 
			explicit Study_Task(std::wstring& _string);
			Study_Task(const Study_Task& /*_classObject*/) = delete;
			Study_Task(Study_Task&& /*_classObject*/) = delete;
			virtual ~Study_Task();

			//상태 설정 함수
			void SetStatus(TaskStatus _status);
			//내용 설정 함수
			void SetString(const std::wstring& _string);

			//상태 획득 함수
			void GetStatus(std::wstring& _string);
			//내용 획득 함수
			void GetString(std::wstring& _string);
			//ToDO 전체 내용 획득 함수
			void GetFullData(std::wstring& _string);

		private:
			//ToDo 상태
			TaskStatus m_status;
			//ToDo 내용
			std::wstring m_string;
		};
	}
}

#endif