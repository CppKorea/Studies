#ifndef	STUDY_TASK_H__
#define STUDY_TASK_H__

namespace Manager
{
	namespace Func_Object
	{
		class Study_Task : public Default::Study_Object
		{
		public:
			explicit Study_Task();
			Study_Task(const Study_Task& /*_classObject*/) = delete;
			Study_Task(Study_Task&& /*_classObject*/) = delete;
			virtual ~Study_Task();

			void AddColumn(std::wstring _key);
			void AddColumns(std::vector<std::wstring> _keys);
			void SetValue(std::wstring _key, std::wstring _value);
			void AddData(std::wstring _key, std::wstring _value);
			void AddDatas(std::vector<std::wstring> _keys, std::vector<std::wstring> _values);

			std::wstring GetShowData();

		private:
			std::vector<std::wstring> m_columns;
			std::unordered_map<std::wstring, std::wstring> m_datas;
		};
	}
}

#endif