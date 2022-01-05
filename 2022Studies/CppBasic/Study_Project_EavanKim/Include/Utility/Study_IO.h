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
		static int ScreenClear()
		{
			//아주 간단하게 콘솔에 명령을 보내서 처리할 수 있습니다.
			//system("cls");

			//Debug에선 잘 초기화 되다가 최적화 코드를 타면서 초기화 안되는 경우가 발생하면 엉뚱한 경우에 피를 보는 경우가 많습니다.
			//선언과 함께 초기화 하는 습관은 프로그램을 업으로 삼게 되셨을 때 여러분의 퇴근시간을 방어하는데 좋습니다.
			COORD CursorResetPosition = { 0, 0 };
			DWORD count = 0;
			DWORD cellCount = 0;

			//이 프로그램의 출력을 담당하는 OUTPUT Buffer에 대해 Windows OS에서 제어를 위해 할당하는 정수형 HANDLE값을 얻어옵니다.
			HANDLE StdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (StdOutHandle == INVALID_HANDLE_VALUE)
				return 1;

			//Windows에서 콘솔 화면 정보를 정의한 구조체입니다.
			//올바른 함수를 통해 얻어오면 내부에 선언된 변수를 통해 정보를 얻을 수 있습니다.
			CONSOLE_SCREEN_BUFFER_INFOEX ScreenBufferInfo;

			//메모리를 한 번 정리해줍니다.
			ZeroMemory(&ScreenBufferInfo, sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));

			//ZeroMemory로 초기화된 객체에 올바른 동작을 위한 객체 사이즈 정보값을 입력합니다.
			ScreenBufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

			//현재 화면 정보를 얻어옵니다.
			if (!GetConsoleScreenBufferInfoEx(StdOutHandle, &ScreenBufferInfo))
				return 2;

			//화면의 전체 버퍼 내 문자 갯수를 구합니다.
			cellCount = ScreenBufferInfo.dwSize.X * ScreenBufferInfo.dwSize.Y;

			//위에서 구한 버퍼의 크기만큼 공백 문자로 덮어버립니다.
			//마지막의 count값은 처리된 갯수입니다.
			if (!FillConsoleOutputCharacter(StdOutHandle, (TCHAR)' ', cellCount, CursorResetPosition, &count))
				return 3;

			//위에서 구한 버퍼의 크기만큼 현재 콘솔의 색상으로 덮어버립니다.
			if (!FillConsoleOutputAttribute(StdOutHandle, ScreenBufferInfo.wAttributes, cellCount, CursorResetPosition, &count))
				return 4;

			//굳이 변수로 만들지 않는다면 이런 식의 호출도 가능합니다.
			//변수로 만들면 디버깅때 해당 변수의 이름을 사용한 조사식 처리가 편리해서 좋습니다.
			//SetConsoleCursorPosition(StdOutHandle, {0, 0});
			SetConsoleCursorPosition(StdOutHandle, CursorResetPosition);

			return 0;
		}

		//콘솔 출력 3형제의 반복 구간을 한 방에 처리하기 위한 함수입니다.
		static int CreatePadding(int _stringSize, int _screenSize, wchar_t _paddingCharactor, std::wstring& _paddingResult)
		{
			int PaddingCount = _screenSize - _stringSize;
			if (0 > PaddingCount)
			{
				return -1;
			}
			else if (0 == PaddingCount)
			{
				return 0;
			}
			else
			{
				_paddingResult.clear();
				_paddingResult.resize(PaddingCount + 1);
				wmemset(_paddingResult.data(), _paddingCharactor, PaddingCount);
				_paddingResult[PaddingCount - 1] = L'\0';
			}

			return PaddingCount;
		}

		//내용을 만드는데 사용되는 함수입니다.
		//기본적으로 한 줄을 사용하는 가정이며 가급적 짧을수록 좋습니다.
		static int ShowLine(const std::wstring& _string, int _screenSize, wchar_t _paddingCharactor = L' ')
		{
			std::wstring paddingString;
			int ResultCount = CreatePadding(_string.length(), _screenSize, _paddingCharactor, paddingString);
			if (0 < ResultCount)
			{
				std::wcout << _string;
				std::wcout << paddingString;
				std::wcout << std::endl;
			}
			else if (0 == ResultCount)
			{
				std::wcout << _string << std::endl;
			}
			else
			{
				return -1;
			}

			return 0;
		}

		//사용자 입력을 받아들여서 처리합니다.
		static bool WaitInput(const std::wstring& _message, std::wstring& _getBuffer)
		{
			_getBuffer.clear();
			std::wcout << _message + L" :" << std::endl;
			std::wcin >> _getBuffer;

			if (_getBuffer.length())
				return true;
			else
				return false;
		}

		//사용자 입력을 받아들여서 처리합니다.
		static bool WaitInput(const std::wstring& _message, int& _get)
		{
			std::wcout << _message + L" :" << std::endl;
			std::wcin >> _get;

			return true;
		}

		//사용자 입력을 받아들여서 처리합니다.
		static bool WaitInput(const std::wstring& _message, float& _get)
		{
			std::wcout << _message + L" :" << std::endl;
			std::wcin >> _get;

			return true;
		}

		//&를 사용한 레퍼런스 표기는 값이 함수를 호출하는 스택에 선언된 것을 그대로 이어서 쓰게 합니다.
		//이 기법은 불필요한 복사를 막아서 성능을 올리는데도 쓰이지만, __in / __out의 의미를 내포시킬 수 있습니다.
		//const는 이 값에 변경이 발생하지 않도록 제한하는 선언입니다.
		//그러므로, _saveData는 Save함수 안에 호출한 스택의 값을 그대로 사용하지만 내부에서 변경되지 않으므로 함수에게 정보를 제공하는 용도일 뿐임을 명시하고 있습니다.
		//_loadData의 경우에는 Load함수 안에 호출한 스택의 값을 그대로 사용하는데 내부에서 변경될 수 있으므로 함수를 거치고 나오면 값이 변경되어 있을 수 있는, 출력용 변수임을 짐작할 수 있습니다.
		//반환자를 사용하지 않는 것 역시 불필요한 복사를 막기 위함입니다.
		//다만 이번에 작성된 코드는 함수의 동작이 올바른지의 유무를 반환자로 처리함으로서 동작때 처리를 연동하기 위함입니다.
		static int DataSave(const std::wstring& _FileName, const std::wstring& _saveData)
		{
			FILE* pFile = nullptr;

			if (0 == _wfopen_s(&pFile, _FileName.c_str(), L"w, ccs=UTF-8"))
			{
				fwrite(_saveData.data(), sizeof(wchar_t), _saveData.length(), pFile);
			}
			fclose(pFile);

			return 0;
		}
		static int DataLoad(const std::wstring& _FileName, std::wstring& _result)
		{
			FILE* pFile = nullptr;

			if (0 == _wfopen_s(&pFile, _FileName.c_str(), L"r, ccs=UTF-8"))
			{
				wchar_t Buffer[1024];
				while (!feof(pFile))
				{
					ZeroMemory(Buffer, 1024 * sizeof(wchar_t));
					fgetws(Buffer, 1024, pFile);
					_result.append(Buffer);
				}
				fclose(pFile);
			}
			else
			{
				return -1;
			}

			return 0;
		}
	}
}

#endif