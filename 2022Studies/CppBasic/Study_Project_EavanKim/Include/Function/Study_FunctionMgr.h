#ifndef STUDY_FUNCTIONMGR_H__
#define STUDY_FUNCTIONMGR_H__

/*
*
* (※경고※) 무근본 자기류 코드 작성법이 사용되었습니다.
* 코드 작성자가 실수하는 부분들을 막으려는 개인적인 작성법이 사용되어 있습니다.
* 코드 작성에 대한 방법은 참조하시지 마시고 이런 생각이 있구나 정도만 참고하여 주십시오.
*
* 프로그램에 대해 완전 처음 도전하신다면 굳이 확인하지 않으셔도 상관없는 내용입니다.
*
* Localize Manager
* 프로그램에서 고정적으로 출력되는 글자가 실행 인자에 맞춰 한/영 전환이 되도록 조치합니다.
* std::exception은 기본적으로 char*를 다루므로, Unicode에 맞는 에러를 출력할 수 있는 에러 객체도 하나 추가하였습니다.
*
* 프로그램 규모적으로 보았을때 매우 뻘쭘한 기능입니다.
* 단순히 이런 문제에 부딪혔을 때 이런 식의 베이스로 작업하실 수 있다 같은 예제입니다.
*
*/

namespace Manager
{
	//주의사항
	//result나 parameter에 배열 데이터를 넘겨서는 안됩니다.
	//가장 안전한 방법은 상속을 통해 소멸자의 delete를 배열 삭제를 고려한 대상으로 고치거나
	//사용하는 대상을 무조건 구조체로 한정해서 구조체가 삭제될 때 배열을 처리하는 것 입니다.
	struct Function_Parameter_Result
	{
		Function_Parameter_Result(std::wstring _key, void* _result = nullptr, void* _parameter = nullptr)
			: key(_key)
			, parameter(_parameter)
			, result(_result)
		{

		}

		~Function_Parameter_Result()
		{
			if (parameter)
				delete parameter;
			if (result)
				delete result;
		}

		std::wstring key;
		void* parameter;
		void* result;
	};

	struct Function_Struct
	{
		Function_Struct(std::wstring _key, void(*_function)(Function_Parameter_Result*))
			: key(_key)
			, function(_function)
		{

		}

		//함수 포인터는 프로그램 실행 시 Code영역에 게시되는 함수의 위치를 사용하는 것 입니다.
		//해제할 때 삭제하지 않도록 주의합니다.
		~Function_Struct()
		{
			function = nullptr;
		}

		void Do(Function_Parameter_Result* _result)
		{
			function(_result);
		}

		std::wstring key;
		void(*function)(Function_Parameter_Result*);
	};

	class Study_FunctionMgr
	{
	public:

		//@@'단일자 구조(Singleton Pattern)'
		//개인적인 방식으로 변형한 구조입니다.
		//일반적으로 GetInstance 안에서 검사를 통해 작업하므로 Initialize_Mgr을 구현하는데
		//여러 문제로 복잡한 검사가 들어갈 때가 있습니다.
		//애초에 문제를 단순하게 해결하기 위해 구분되어 사용합니다.
		static void Initialize_Mgr();
		static Study_FunctionMgr* GetInstance();
		void Release();
		//~@@'단일자 구조(Singleton Pattern)'

		void AddFunction(Function_Struct&);
		void RemoveFunction(std::wstring);
		void Do(Function_Parameter_Result*);

	private:
		//@@'단일자 구조(Singleton Pattern)'
		//생성과 삭제를 외부에서 제어할 수 없도록 막아버린 부분입니다.
		explicit Study_FunctionMgr();

		//'기본 생성자 제거' 키워드로 찾아보시면 설명이 나와있습니다.
		Study_FunctionMgr(const Study_FunctionMgr& /*_classObject*/) = delete;
		Study_FunctionMgr(Study_FunctionMgr&& /*_classObject*/) = delete;

		~Study_FunctionMgr();
		//~@@'단일자 구조(Singleton Pattern)'

	public:


	private:
		std::map<std::wstring, Function_Struct> m_FunctionBase;

		//@@'단일자 구조(Singleton Pattern)'
		//프로그램에서 유일하게 존재하는 객체를 선언합니다.
		//클래스 안에 선언하면 클래스 명으로 namespace 효과를 받기 때문에 패턴을 구현할때 동일한 변수명을 사용할 수 있어서 좋습니다.
		//정 클래스 안에 넣기 싫으시다면 외부에 선언하더라도 프로그램 전역에서 딱 하나의 객체만 유지되면 아무 이상이 없다고 생각합니다.
		static Study_FunctionMgr* m_instance;
		//~@@'단일자 구조(Singleton Pattern)'
	};
}

#endif