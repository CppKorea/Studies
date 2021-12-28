#include "headers_custom.h"

//Windows �������� ������ ����մϴ�.
//������� OS �������� ��찡 �����Ƿ� ���� �� �ڵ带 ��� OS���� ó���� �� �ְ� �Ϸ��ٰ�
//������ ������ �� �� �ֱ� �����Դϴ�.
#include <Windows.h>

namespace Manager
{
	namespace Study_IO
	{
		int ScreenClear()
		{
			//���� �����ϰ� �ֿܼ� ����� ������ ó���� �� �ֽ��ϴ�.
			//system("cls");

			//Debug���� �� �ʱ�ȭ �Ǵٰ� ����ȭ �ڵ带 Ÿ�鼭 �ʱ�ȭ �ȵǴ� ��찡 �߻��ϸ� ������ ��쿡 �Ǹ� ���� ��찡 �����ϴ�.
			//����� �Բ� �ʱ�ȭ �ϴ� ������ �������� ��ٽð��� ����ϴµ� �����ϴ�.
			COORD CursorResetPosition = { 0, 0 };
			DWORD count = 0;
			DWORD cellCount = 0;

			//�� ���α׷��� ����� ����ϴ� OUTPUT Buffer�� ���� Windows OS���� ��� ���� �Ҵ��ϴ� ������ HANDLE���� ���ɴϴ�.
			HANDLE StdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (StdOutHandle == INVALID_HANDLE_VALUE)
				return 1;

			//Windows���� �ܼ� ȭ�� ������ ������ ����ü�Դϴ�.
			//�ùٸ� �Լ��� ���� ������ ���ο� ����� ������ ���� ������ ���� �� �ֽ��ϴ�.
			CONSOLE_SCREEN_BUFFER_INFOEX ScreenBufferInfo;

			//�޸𸮸� �� �� �������ݴϴ�.
			ZeroMemory(&ScreenBufferInfo, sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));

			//ZeroMemory�� �ʱ�ȭ�� ��ü�� �ùٸ� ������ ���� ��ü ������ �������� �Է��մϴ�.
			ScreenBufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

			//���� ȭ�� ������ ���ɴϴ�.
			if (!GetConsoleScreenBufferInfoEx(StdOutHandle, &ScreenBufferInfo))
				return 2;

			//ȭ���� ��ü ���� �� ���� ������ ���մϴ�.
			cellCount = ScreenBufferInfo.dwSize.X * ScreenBufferInfo.dwSize.Y;

			//������ ���� ������ ũ�⸸ŭ ���� ���ڷ� ��������ϴ�.
			//�������� count���� ó���� �����Դϴ�.
			if (!FillConsoleOutputCharacter(StdOutHandle, (TCHAR)' ', cellCount, CursorResetPosition, &count) )
				return 3;

			//������ ���� ������ ũ�⸸ŭ ���� �ܼ��� �������� ��������ϴ�.
			if (!FillConsoleOutputAttribute(StdOutHandle, ScreenBufferInfo.wAttributes, cellCount, CursorResetPosition, &count))
				return 4;

			//���� ������ ������ �ʴ´ٸ� �̷� ���� ȣ�⵵ �����մϴ�.
			//������ ����� ����붧 �ش� ������ �̸��� ����� ����� ó���� ���ؼ� �����ϴ�.
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
