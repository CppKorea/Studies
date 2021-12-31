#include "Grouping/headers_custom.h"

namespace Manager
{
	//@@'단일자 구조(Singleton Pattern)'

	//'정적 맴버 변수(Static Member Value)'는 cpp에서 초기화가 되어야 합니다.
	//또한 단일자 구조에서는 꼭 0, NULL, nullptr로 초기화 해 두시는것이 좋습니다.
	//Debug에서는 디버깅을 위해 할당되는 값들을 알아서 0으로 정렬해주는 등의 친절을 배풀다가
	//Release에서는 최적화로 초기화가 안되는 바람에 엉뚱한 충돌이 발생하기도 합니다.
	//이는 굳이 단일자가 아니더라도 '포인터'를 사용할때 가장 중요한 처리입니다.
	Study_Localize* Study_Localize::m_instance = nullptr;
	//~@@'단일자 구조(Singleton Pattern)'

//Public Function
	//@@'단일자 구조(Singleton Pattern)'
	void Study_Localize::Initialize_Mgr(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName)
	{
		//정적 객체인 m_Instance는 올바르게 사용한다면 프로그램 전체에서 유일하게 존재하는 변수명입니다.
		//단일자는 프로그램 전체에서 객체를 딱 하나로만 유지할 필요가 있는 구조이므로 할당이 된 적이 있는지 검사합니다.
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		if (nullptr == m_instance)
		{
			//예전에 선언된 적이 없다면 새로운 객체를 할당합니다.
			m_instance = new Study_Localize(_LocaleStringFilePath, _LocaleStringFileName);
		}
	}

	Study_Localize* Study_Localize::GetInstance()
	{
		//어떤 위치에서든 이 함수를 통해 단일 할당된 단일자 객체에 접근합니다.
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		return m_instance;
	}

	void Study_Localize::Release()
	{
		//할당 된 적이 있을때만 해제하는 동작으로 구성함으로서 여기저기서 불릴 수 있는 단일자 구성 특성때문에 사용하는 검사입니다.
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		if (nullptr != m_instance)
		{
			//할당 한 적이 있다면 삭제를 수행합니다.
			delete m_instance;
			//단일자는 삭제되고 나서 다른 동작이 발생하기 전에 m_Instance에 대해 검사하고 동작하는데다가,
			//이 Release 동작이 올바르게 수행되기 위해서 꼭 객체 포인터를 0, NULL, nullptr 등으로 정리해놔야 합니다.
			m_instance = nullptr;
		}
	}
	//~@@'단일자 구조(Singleton Pattern)'

	bool Study_Localize::GetLocalizeString(const std::wstring& _stringKey, std::wstring& _Result)
	{
		//기본적으로 성공하는 단 하나의 케이스를 제외하면 모두 실패로 처리하도록 초기화 합니다.
		bool Result = false;

		//미리 준비한 컨테이너에서 키를 사용하여 데이터를 검색합니다.
		std::map<std::wstring, std::wstring>::const_iterator Target = m_stringDataBase.find(_stringKey);

		//검출되었는지 검사합니다.
		//Map의 find명령은 데이터가 없다면 iteration 순회를 끝까지 보내버리므로, end와 일치하는 경우 데이터가 없는 상황입니다.
		if (Target != m_stringDataBase.end())
		{
			//찾아낸 데이터를 반환값에 싣고 결과값을 성공으로 처리합니다.
			_Result = Target->second;
			Result = true;
		}
		else
		{
			//찾아낸 데이터가 없지만 프로그램 자체를 실행하는데 문제가 없도록 빈 문자를 표현하는 임의의 글자를 반환값에 싣습니다.
			//에러 기록을 로그로 남기고 빠져나갑니다.
			_Result = L"####";
			std::wstring CreateErrorMessage(L"!!!Cannot Find String Data!!! | Key : " + _stringKey);
			OutputDebugStringW(CreateErrorMessage.c_str());
		}

		return Result;
	}

	Study_Localize::Study_Localize(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName)
	{
		//혹시 에러가 나면 상태를 변경하기 위한 매니저 포인터를 들고옵니다.
		Status* StatusMgr = Status::GetInstance();

		//상태 메니저가 초기화 되지 않았다면 게임 자체에 문제가 있다고 판단합니다.
		if ( nullptr != StatusMgr )
		{
			//혹시 이미 문제가 있는 상태인지 확인합니다.
			PROGRAM_RUN_STATE LastStatus = StatusMgr->GetProgramRunState();
			if ((PROGRAM_RUN_STATE::EXCEPTION == LastStatus) || (PROGRAM_RUN_STATE::EXIT == LastStatus))
				return;

			//경로와 파일명으로 FullPath를 만들어냅니다.
			std::wstring FullPath = L"";
			FullPath.append(_LocaleStringFilePath);
			FullPath.append(L"\\");
			FullPath.append(_LocaleStringFileName);
			std::wstring ReadResult;
			ReadResult.clear();

			//Localize 파일에서 데이터를 읽어들입니다.
			int LoadResult = Study_IO::DataLoad(FullPath, ReadResult);

			//반환 코드에 맞게 작업합니다.
			switch (LoadResult)
			{
			case 0: //성공
			{
				//마지막이 ;로 끝나는지 검사합니다.
				//그렇지 않다면 오작동의 위험이 있는 오염된 데이터로 취급합니다.
				if (L';' == ReadResult[ReadResult.length() - 1])
				{
					//파일로부터 가져온 문자열이 빌 때 까지 순회합니다.
					while (0 != ReadResult.length())
					{
						//; 위치를 찾아서 문자열 절단 기준점으로 삼습니다.
						size_t StringSize = ReadResult.find(L';');
						//혹시 문자열이 잘못되서 ;를 찾아내지 못하면 에러로 취급합니다.
						if (StringSize < ReadResult.length())
						{
							//문자열을 절단합니다.
							std::wstring SplitString(ReadResult.data(), StringSize, std::allocator<wchar_t>());
							//절단된 문자열을 삭제한 문자열로 갱신합니다.
							ReadResult = std::wstring(ReadResult, StringSize + 1, std::allocator<wchar_t>());

							//`위치를 찾아서 Key/Value로 절단할 기준점으로 삼습니다.
							size_t KeySize = SplitString.find(L'`');
							//혹시 문자열이 잘못되어서 `를 찾아내지 못하면 에러로 취급합니다.
							if (KeySize < SplitString.length())
							{
								//Key값을 잘라냅니다.
								std::wstring Key(SplitString.data(), KeySize, std::allocator<wchar_t>());
								//남은 문자열에서 `를 없애고 value를 가져옵니다.
								std::wstring Value(SplitString, KeySize + 1, std::allocator<wchar_t>());
								//두 자료를 모아 하나의 정보로 만들어 저장합니다.
								m_stringDataBase.insert(std::make_pair(Key, Value));
							}
							else
							{
								throw std::exception("Localize Data File Is Corrupted!!!");
							}
						}
						else
						{
							throw std::exception("Localize Data File Is Corrupted!!!");
						}
					}
				}
				else
				{
					throw std::exception("Localize Data File Is Corrupted!!!");
				}
			}
				break;
			case 1:
				//원래라면 정상적인데 다른 프로그램이 점유하고 있어서 문제가 생겼습니다.
				//StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				//StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				//StatusMgr->UpdateLastStateString(L"[-][Error][Localize Initialize] : File Already Used Another Program");
				break;
			case -1:
				//파일은 있는데 읽어들일 때 어째서인지 실패했습니다.
				//StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				//StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				//StatusMgr->UpdateLastStateString(L"[-][Error][Localize Initialize] : Cannot Read Localize File");
				break;
			case -2:
				//파일이 없습니다.
				//StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				//StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				//StatusMgr->UpdateLastStateString(L"[-][Error][Localize Initialize] : Cannot Find Localize File");
				break;
			default:
				break;
			}
		}
	}

	Study_Localize::~Study_Localize()
	{
		m_stringDataBase.clear();
	}
}
