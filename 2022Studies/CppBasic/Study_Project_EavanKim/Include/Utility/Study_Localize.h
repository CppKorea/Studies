#ifndef STUDY_LOCALIZE_H__
#define STUDY_LOCALIZE_H__

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
	class Study_Localize
	{
	public:

		//@@'단일자 구조(Singleton Pattern)'
		//개인적인 방식으로 변형한 구조입니다.
		//일반적으로 GetInstance 안에서 검사를 통해 작업하므로 Initialize_Mgr을 구현하는데
		//여러 문제로 복잡한 검사가 들어갈 때가 있습니다.
		//애초에 문제를 단순하게 해결하기 위해 구분되어 사용합니다.
		static void Initialize_Mgr(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName);
		static Study_Localize* GetInstance();
		void Release();
		//~@@'단일자 구조(Singleton Pattern)'

		//글자를 얻어옵니다.
		//일치하는 키가 없을 땐 false가 나옵니다.
		bool GetLocalizeString(const std::wstring& _stringKey, std::wstring& _Result);

	private:
		//@@'단일자 구조(Singleton Pattern)'
		//생성과 삭제를 외부에서 제어할 수 없도록 막아버린 부분입니다.
		explicit Study_Localize(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName);

		//'기본 생성자 제거' 키워드로 찾아보시면 설명이 나와있습니다.
		Study_Localize() = delete;
		Study_Localize(const Study_Localize& /*_classObject*/) = delete;
		Study_Localize(Study_Localize&& /*_classObject*/) = delete;

		~Study_Localize();
		//~@@'단일자 구조(Singleton Pattern)'

	public:


	private:
		std::map<std::wstring, std::wstring> m_stringDataBase;

		//@@'단일자 구조(Singleton Pattern)'
		//프로그램에서 유일하게 존재하는 객체를 선언합니다.
		//클래스 안에 선언하면 클래스 명으로 namespace 효과를 받기 때문에 패턴을 구현할때 동일한 변수명을 사용할 수 있어서 좋습니다.
		//정 클래스 안에 넣기 싫으시다면 외부에 선언하더라도 프로그램 전역에서 딱 하나의 객체만 유지되면 아무 이상이 없다고 생각합니다.
		static Study_Localize* m_instance;
		//~@@'단일자 구조(Singleton Pattern)'
	};
}

#endif