#ifndef STUDY_IO_H__
#define STUDY_IO_H__

/*
*
* (�ذ���) ���ٺ� �ڱ�� �ڵ� �ۼ����� ���Ǿ����ϴ�.
* �ڵ� �ۼ��ڰ� �Ǽ��ϴ� �κе��� �������� �������� �ۼ����� ���Ǿ� �ֽ��ϴ�.
* �ڵ� �ۼ��� ���� ����� �����Ͻ��� ���ð� �̷� ������ �ֱ��� ������ �����Ͽ� �ֽʽÿ�.
*
* I/O Manager
* � ���·ε� Input�� Output�� �ٷ�� ���뿡 ���� �޴����Դϴ�.
*
* ��� �䱸����
* 1. �����͸� ������ �������� ������ �� �־�� �մϴ�.
* 2. �����ߴ� �����͸� �о���� �� �־�� �մϴ�.
* 3. � ���·ε� ���α׷����� ������ ����� 1�� �̻��� ������� ǥ���� �� �־�� �մϴ�.
*/

namespace Manager
{
	namespace Study_IO
	{
		//Console
		//int�� ��ȯ��Ű�� ������ ���ο��� ����ϴ� �Լ� �� ���� �������� ���� �Լ����� ������ �߻����� ��,
		//��� �Լ����� ������ �Ͼ���� �����ϱ� �����Դϴ�.
		//������ ��ü���� ErrorCode ���� ���Դϴ�.
		static int ScreenClear()
		{
			//���� �����ϰ� �ֿܼ� ����� ������ ó���� �� �ֽ��ϴ�.
			//system("cls");

			//Debug���� �� �ʱ�ȭ �Ǵٰ� ����ȭ �ڵ带 Ÿ�鼭 �ʱ�ȭ �ȵǴ� ��찡 �߻��ϸ� ������ ��쿡 �Ǹ� ���� ��찡 �����ϴ�.
			//����� �Բ� �ʱ�ȭ �ϴ� ������ ���α׷��� ������ ��� �Ǽ��� �� �������� ��ٽð��� ����ϴµ� �����ϴ�.
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
			if (!FillConsoleOutputCharacter(StdOutHandle, (TCHAR)' ', cellCount, CursorResetPosition, &count))
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

		//�ܼ� ��� 3������ �ݺ� ������ �� �濡 ó���ϱ� ���� �Լ��Դϴ�.
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

		//������ ����µ� ���Ǵ� �Լ��Դϴ�.
		//�⺻������ �� ���� ����ϴ� �����̸� ������ ª������ �����ϴ�.
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

		//����� �Է��� �޾Ƶ鿩�� ó���մϴ�.
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

		//����� �Է��� �޾Ƶ鿩�� ó���մϴ�.
		static bool WaitInput(const std::wstring& _message, int& _get)
		{
			std::wcout << _message + L" :" << std::endl;
			std::wcin >> _get;

			return true;
		}

		//����� �Է��� �޾Ƶ鿩�� ó���մϴ�.
		static bool WaitInput(const std::wstring& _message, float& _get)
		{
			std::wcout << _message + L" :" << std::endl;
			std::wcin >> _get;

			return true;
		}

		//&�� ����� ���۷��� ǥ��� ���� �Լ��� ȣ���ϴ� ���ÿ� ����� ���� �״�� �̾ ���� �մϴ�.
		//�� ����� ���ʿ��� ���縦 ���Ƽ� ������ �ø��µ��� ��������, __in / __out�� �ǹ̸� ������ų �� �ֽ��ϴ�.
		//const�� �� ���� ������ �߻����� �ʵ��� �����ϴ� �����Դϴ�.
		//�׷��Ƿ�, _saveData�� Save�Լ� �ȿ� ȣ���� ������ ���� �״�� ��������� ���ο��� ������� �����Ƿ� �Լ����� ������ �����ϴ� �뵵�� ������ ����ϰ� �ֽ��ϴ�.
		//_loadData�� ��쿡�� Load�Լ� �ȿ� ȣ���� ������ ���� �״�� ����ϴµ� ���ο��� ����� �� �����Ƿ� �Լ��� ��ġ�� ������ ���� ����Ǿ� ���� �� �ִ�, ��¿� �������� ������ �� �ֽ��ϴ�.
		//��ȯ�ڸ� ������� �ʴ� �� ���� ���ʿ��� ���縦 ���� �����Դϴ�.
		//�ٸ� �̹��� �ۼ��� �ڵ�� �Լ��� ������ �ùٸ����� ������ ��ȯ�ڷ� ó�������μ� ���۶� ó���� �����ϱ� �����Դϴ�.
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