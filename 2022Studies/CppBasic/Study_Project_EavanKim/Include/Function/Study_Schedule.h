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
* ToDo와 1:1로 매칭되는 Task 객체를 관리하는 객체입니다.
* 
*/

namespace Manager
{
	//Schedule 객체의 상태를 표현하는 enum입니다.
	enum class ScheduleStatus
	{
		INITIALIZE //초기화 중입니다.
		, IDLE //기본 대기상태 입니다.
		, ADD // ToDo를 추가중입니다.
		, REMOVE // ToDo를 삭제중입니다.
		, MANAGE // ToDo를 관리중입니다.
		, SAVE // ToDo를 저장합니다
		, LOAD // ToDo를 불러옵니다.
		, END
	};

	class Study_Schedule
	{
	public:
		//입출력 형태를 표현하는 enum입니다.
		enum class IOType
		{
			OUT_TEXT // 글자를 출력합니다.
			, OUT_TITLE // 제목을 출력합니다.
			, OUT_CUSTOMTEXT // 임의의 문자열을 단순 출력 합니다.
			, IN_INT // 정수값을 받아옵니다.
			, IN_FLOAT // 실수값을 받아옵니다.
			, IN_TEXT // 문자열 입력을 받습니다.
			, IN_SUSPEND // 멈추기 위한 의미없는 입력입니다.
			, SHOW_LIST // ToDo List를 출력합니다.
		};

		//Schedule에서 입출력에 대해 처리하는 객체를 정의합니다.
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

			//어떻게 동작할지 정의된 Enum입니다.
			IOType type;
			//값이 잘못된 내용이 있는지 검사하는 bool입니다.
			bool valied;
			//Localize에서 검색할 키값입니다.
			std::wstring textkey;
			//출력할 문자열입니다.
			std::wstring text;
			//입력받는 정수값을 저장하는 위치입니다.
			int input_int;
			//입력받는 실수값을 저장하는 위치입니다.
			float input_float;
			//입력받는 문자열을 저장하는 위치입니다.
			std::wstring input_text;
		};

		explicit Study_Schedule();
		~Study_Schedule();

		//전체 리스트를 출력합니다.
		//_Interrupt를 true로 맞추면 입력이 끝나기 전 까지 리스트 출력에 머무릅니다.
		int ShowTaskList(bool _Interrupt = false);

		//ToDo List에 입력받은 글자를 입력한 새로운 Task를 생성한다.
		void AddTask(std::wstring _Task);
		
		//ToDo List에서 대상을 바로 삭제합니다.
		void RemoveTask(int _Task);

		//Task Setup Process.
		//안에서 ProcessIOSetupList를 수행하면서 입력을 받아 처리
		int TaskManage(Default::Study_Ptr<Func_Object::Study_Task>& _TaskPtr);

		//입출력 관련 처리 절차 수행
		int ProcessIOSetupList(std::vector<Schedule_IO_Setup>& _list);
		
		//불러온 데이터 세팅 함수
		void SetLoadedData(std::wstring& _loadedData);

		//저장할 데이터 생성 함수
		bool CreateSaveData(std::wstring& _createdData);

		//게임 로직 실행
		int Run();

	private:
		ScheduleStatus m_status;
		std::vector<Default::Study_Ptr<Func_Object::Study_Task>> m_taskList;
	};
}

#endif