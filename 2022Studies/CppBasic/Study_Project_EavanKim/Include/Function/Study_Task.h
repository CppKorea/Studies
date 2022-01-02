#ifndef	STUDY_TASK_H__
#define STUDY_TASK_H__

/*
*
* (�ذ���) ���ٺ� �ڱ�� �ڵ� �ۼ����� ���Ǿ����ϴ�.
* �ڵ� �ۼ��ڰ� �Ǽ��ϴ� �κе��� �������� �������� �ۼ����� ���Ǿ� �ֽ��ϴ�.
* �ڵ� �ۼ��� ���� ����� �����Ͻ��� ���ð� �̷� ������ �ֱ��� ������ �����Ͽ� �ֽʽÿ�.
*
* Study_Task
* ToDo�� �� ���� �����ϴ� �ڷ��� ���տ� ���� ��ü�Դϴ�.
*
*/

namespace Manager
{
	namespace Func_Object
	{
		//�ڷ� �� �ϳ��� ToDo �����Դϴ�.
		enum class TaskStatus
		{
			NONE
			, PROGRASS
			, DONE
			, END
		};

		//�ڷ��� ������ ������ ��ü�� �ٷ�� ���� �������� �����Դϴ�.
		class Study_Task : public Default::Study_Object
		{
		public:
			//������ �� �ʱⰪ���� 
			explicit Study_Task(std::wstring& _string);
			Study_Task(const Study_Task& /*_classObject*/) = delete;
			Study_Task(Study_Task&& /*_classObject*/) = delete;
			virtual ~Study_Task();

			//���� ���� �Լ�
			void SetStatus(TaskStatus _status);
			//���� ���� �Լ�
			void SetString(const std::wstring& _string);

			//���� ȹ�� �Լ�
			void GetStatus(std::wstring& _string);
			//���� ȹ�� �Լ�
			void GetString(std::wstring& _string);
			//ToDO ��ü ���� ȹ�� �Լ�
			void GetFullData(std::wstring& _string);

		private:
			//ToDo ����
			TaskStatus m_status;
			//ToDo ����
			std::wstring m_string;
		};
	}
}

#endif