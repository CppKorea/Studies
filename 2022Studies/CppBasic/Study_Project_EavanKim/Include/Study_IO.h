#ifndef STUDY_IO_H__
#define STUDY_IO_H__

/*
* 
* (※경고※) 무근본 자기류 코드 작성법이 사용되었습니다.
* 코드 작성자가 실수하는 부분들을 막으려는 개인적인 작성법이 사용되어 있습니다.
* 코드 작성에 대한 방법은 참조하시지 마시고 이런 생각이 있구나 정도만 참고하여 주십시오.
* 
* I/O Manager
* 어떤 형태로든 Input과 Output을 다루는 내용에 대한 메니저입니다.
*
* 기능 요구사항
* 1. 데이터를 파일의 형식으로 저장할 수 있어야 합니다.
* 2. 저장했던 데이터를 읽어들일 수 있어야 합니다.
* 3. 어떤 형태로든 프로그램에서 구현할 기능을 1개 이상의 방식으로 표출할 수 있어야 합니다.
*/

namespace Manager
{
	namespace Study_IO
	{
		//Console
		//int로 반환시키는 이유는 내부에서 사용하는 함수 중 직접 구현하지 않은 함수에서 문제가 발생했을 때,
		//어느 함수에서 문제가 일어났는지 추적하기 위함입니다.
		//일종의 자체적인 ErrorCode 같은 것입니다.
		static int ScreenClear();
		//제목을 만드는데 사용되는 함수입니다.
		//기본적으로 한 줄을 사용하는 가정이며 가급적 짧을수록 좋습니다.
		static bool ShowTitle(const std::wstring& _string);
		//내용을 만드는데 사용되는 함수입니다.
		static bool ShowLine(const std::wstring& _string);
		//출력을 마무리하는데 쓰이는 함수입니다.
		static bool ShowEnd(const std::wstring& _string);
		//사용자 입력을 받아들여서 처리합니다.
		static wchar_t WaitInput();

		//File
#if USE_WINDOWS_ONLY
		// __in 과 __out은 Visual C++ 에서 사용하는 선언입니다.
		// 함수에 집어넣고 안에서 값이 바뀌지 않는 __in 표기와
		// 함수에서 처리가 끝나면 결과값을 받아서 쓰기 위한 __out 표기입니다.
		static bool Save(__in std::wstring& _saveData);
		static bool Load(__out std::wstring& _loadData);
#else
		//굳이 __in / __out을 쓰지 않더라도 이렇게 표현 가능합니다.
		//&를 사용한 레퍼런스 표기는 값이 함수를 호출하는 스택에 선언된 것을 그대로 이어서 쓰게 합니다.
		//이 기법은 불필요한 복사를 막아서 성능을 올리는데도 쓰이지만, __in / __out의 의미를 내포시킬 수 있습니다.
		//const는 이 값에 변경이 발생하지 않도록 제한하는 선언입니다.
		//그러므로, _saveData는 Save함수 안에 호출한 스택의 값을 그대로 사용하지만 내부에서 변경되지 않으므로 함수에게 정보를 제공하는 용도일 뿐임을 명시하고 있습니다.
		//_loadData의 경우에는 Load함수 안에 호출한 스택의 값을 그대로 사용하는데 내부에서 변경될 수 있으므로 함수를 거치고 나오면 값이 변경되어 있을 수 있는, 출력용 변수임을 짐작할 수 있습니다.
		//반환자를 사용하지 않는 것 역시 불필요한 복사를 막기 위함입니다.
		//다만 이번에 작성된 코드는 함수의 동작이 올바른지의 유무를 반환자로 처리함으로서 동작때 처리를 연동하기 위함입니다.
		static bool Save(const std::wstring& _saveData);
		static bool Load(std::wstring& _loadData);
#endif
	}
}

#endif