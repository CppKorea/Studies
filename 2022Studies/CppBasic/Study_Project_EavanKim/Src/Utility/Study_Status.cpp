#include "Grouping/headers_custom.h"

namespace Manager
{
	//@@'단일자 구조(Singleton Pattern)'

	//'정적 맴버 변수(Static Member Value)'는 cpp에서 초기화가 되어야 합니다.
	//또한 단일자 구조에서는 꼭 0, NULL, nullptr로 초기화 해 두시는것이 좋습니다.
	//Debug에서는 디버깅을 위해 할당되는 값들을 알아서 0으로 정렬해주는 등의 친절을 배풀다가
	//Release에서는 최적화로 초기화가 안되는 바람에 엉뚱한 충돌이 발생하기도 합니다.
	//이는 굳이 단일자가 아니더라도 '포인터'를 사용할때 가장 중요한 처리입니다.
	Status* Status::m_instance = nullptr;
	//~@@'단일자 구조(Singleton Pattern)'

//Public Function
	//@@'단일자 구조(Singleton Pattern)'
	void Status::Initialize_Mgr()
	{
		//정적 객체인 m_Instance는 올바르게 사용한다면 프로그램 전체에서 유일하게 존재하는 변수명입니다.
		//단일자는 프로그램 전체에서 객체를 딱 하나로만 유지할 필요가 있는 구조이므로 할당이 된 적이 있는지 검사합니다.
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		if (nullptr == m_instance)
		{
			//예전에 선언된 적이 없다면 새로운 객체를 할당합니다.
			m_instance = new Status();
		}
	}

	Status* Status::GetInstance()
	{
		//어떤 위치에서든 이 함수를 통해 단일 할당된 단일자 객체에 접근합니다.
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		return m_instance;
	}

	void Status::Release()
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

	bool Status::CheckProgramRunSanity()
	{
		//최종적으로 체크했을 때 NORMAL 상태가 아니라면 정상이 아니라고 판정합니다.
		//'단일 실행흐름(Single Thread)' 구성에서만 가능한 처리입니다.
		//'다중 실행흐름(Multi Thread)' 구성에서는 다른 Thread에서 다른 상태를 처리할 수 있으므로 일부 예외를 무시하거나 하고 싶다면 EXIT가 아닌지
		//혹은 특정 종료하고 싶은 상태가 아닌지를 확인하는 구성으로 변경해야합니다.
		return PROGRAM_RUN_STATE::NORMAL == m_programRunState;
	}

	PROGRAM_RUN_STATE Status::GetProgramRunState()
	{
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		return m_programRunState;
	}

	PROGRAM_WORK_STATE Status::GetProgramWorkState()
	{
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		return m_programWorkState;
	}

	PROGRAM_RUN_STATE Status::SetProgramRunState(PROGRAM_RUN_STATE _CurrentState)
	{
		PROGRAM_RUN_STATE prevState = m_programRunState;
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		m_programRunState = _CurrentState;

		return prevState;
	}

	PROGRAM_WORK_STATE Status::SetProgramWorkState(PROGRAM_WORK_STATE _CurrentState)
	{
		PROGRAM_WORK_STATE prevState = m_programWorkState;
		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		m_programWorkState = _CurrentState;

		return prevState;
	}

	void Status::UpdateLastStateString(const std::wstring& _UpdateString)
	{
		m_lastStateString = _UpdateString;
	}

//Private Function
	Status::Status()
		: m_programRunState(PROGRAM_RUN_STATE::INITIALIZE)
		, m_programWorkState(PROGRAM_WORK_STATE::INITIALIZE)
	{
		//필요한 초기화 작업을 수행하는 위치입니다.

		//초기화가 끝나면 일반 상태로 변경합니다.
		SetProgramRunState(PROGRAM_RUN_STATE::NORMAL);
		SetProgramWorkState(PROGRAM_WORK_STATE::IDLE);
	}

	Status::~Status()
	{
		std::wcout << L"LastState : " << m_lastStateString << std::endl;

		//이 동작은 헤더 하단의 설명에서 위험한 경우가 발생하는 경우 중 하나입니다.
		if (PROGRAM_RUN_STATE::EXIT != SetProgramRunState(PROGRAM_RUN_STATE::EXIT))
		{
			//Manager::Status는 프로그램의 시작과 끝을 함께하고 실행을 제아하고 있기 때문에 삭제된다면 다른 곳에서 EXIT를 받았어야 올바릅니다.
			//EXIT값이 아니었다는 것은 종료 전 정리 단계를 거치지 않았을 확률이 높습니다. (Ex. EXCEPTION 같은 문제가 발생해서 프로그램이 강제로 종료된다거나 등)
			//기본적으로 Status는 Manager의 삭제 단계에서 가장 마지막에 해제되도록 구성합니다.
			//왜냐하면, 다른 객체들이 해제될 때 마지막 프로그램 상태에 맞게 해제하도록 구성하기 때문입니다.
			//그러므로 여기까지 진입했는데 PROGRAM_RUN_STATE가 EXIT가 아니라면 메모리 누수를 막기 위한 검사와 조치가 필요합니다.
			//RUN_STATE는 프로그램 자체에 대한 '상태 처리기계(State Machine)'이므로 State자체에 대한 안전처리를 수행합니다.

		}

		if (PROGRAM_WORK_STATE::EXIT != SetProgramWorkState(PROGRAM_WORK_STATE::EXIT))
		{
			//Manager::Status는 프로그램의 시작과 끝을 함께하고 실행을 제아하고 있기 때문에 삭제된다면 다른 곳에서 EXIT를 받았어야 올바릅니다.
			//EXIT값이 아니었다는 것은 종료 전 정리 단계를 거치지 않았을 확률이 높습니다. (Ex. EXCEPTION 같은 문제가 발생해서 프로그램이 강제로 종료된다거나 등)
			//기본적으로 Status는 Manager의 삭제 단계에서 가장 마지막에 해제되도록 구성합니다.
			//왜냐하면, 다른 객체들이 해제될 때 마지막 프로그램 상태에 맞게 해제하도록 구성하기 때문입니다.
			//그러므로 여기까지 진입했는데 PROGRAM_RUN_STATE가 EXIT가 아니라면 메모리 누수를 막기 위한 검사와 조치가 필요합니다.
			//WORK_STATE는 프로그램 내부의 동작에 대한 '상태 처리기계(State Machine)'이므로 State외적인 객체에 대한 안전처리를 수행합니다.

		}
	}
}