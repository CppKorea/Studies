#include "headers_custom.h"

//Windows 종속적인 구현을 사용합니다.
//입출력은 OS 종속적인 경우가 많으므로 굳이 이 코드를 모든 OS에서 처리할 수 있게 하려다가
//내용이 산으로 갈 수 있기 때문입니다.
#include <Windows.h>

namespace Manager
{
	namespace Study_IO
	{
		int ScreenClear()
		{
			//아주 간단하게 콘솔에 명령을 보내서 처리할 수 있습니다.
			//system("cls");

			//Debug에선 잘 초기화 되다가 최적화 코드를 타면서 초기화 안되는 경우가 발생하면 엉뚱한 경우에 피를 보는 경우가 많습니다.
			//선언과 함께 초기화 하는 습관은 여러분의 퇴근시간을 방어하는데 좋습니다.
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
			if (!FillConsoleOutputCharacter(StdOutHandle, (TCHAR)' ', cellCount, CursorResetPosition, &count) )
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

		bool ShowTitle(const std::wstring& _string)
		{
			return false;
		}

		bool ShowLine(const std::wstring& _string)
		{
			return false;
		}

		bool ShowEnd(const std::wstring& _string)
		{
			return false;
		}

		wchar_t WaitInput()
		{
			return L'\0';
		}

		bool Save(std::wstring& _saveData)
		{
			return false;
		}

		bool Load(std::wstring& _loadData)
		{
			return false;
		}
	}
}
