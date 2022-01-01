#ifndef	STUDY_TASK_H__
#define STUDY_TASK_H__

namespace Manager
{
	namespace Func_Object
	{
		enum class TaskStatus
		{
			NONE
			, PROGRASS
			, DONE
			, END
		};

		class Study_Task : public Default::Study_Object
		{
		public:
			explicit Study_Task(std::wstring& _string);
			Study_Task(const Study_Task& /*_classObject*/) = delete;
			Study_Task(Study_Task&& /*_classObject*/) = delete;
			virtual ~Study_Task();

			void SetStatus(TaskStatus _status);
			void SetString(const std::wstring& _string);

			void GetStatus(std::wstring& _string);
			void GetString(std::wstring& _string);
			void GetFullData(std::wstring& _string);

		private:
			TaskStatus m_status;
			std::wstring m_string;
		};
	}
}

#endif