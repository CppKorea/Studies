#ifndef STUDY_PROGRAM_H__
#define STUDY_PROGRAM_H__

/*
* (※경고※) 무근본 자기류 코드 작성법이 사용되었습니다.
* 코드 작성자가 실수하는 부분들을 막으려는 개인적인 작성법이 사용되어 있습니다.
* 코드 작성에 대한 방법은 참조하시지 마시고 이런 생각이 있구나 정도만 참고하여 주십시오.
* 
* Manager 예시 겸 프로그램 제어
* 스터디용 디자인 패턴 예제입니다.
* 실제 프로그램에서 사용하려면 더 고려할 사항이 많습니다.
* 어디까지나 이런 방법도 있다 라는 느낌으로 봐 주시기 바랍니다.
* 문제에 대한 설명이 필요하신 분은 파일 하단의 주석을 확인 부탁드립니다.
*/

namespace Manager
{
// 아래 USE_OLD_ENUM에 의해 발생하는 차이는 한 번 찾아보시는 것이 좋다고 생각합니다.
// enum과 enum class의 차이입니다.
#ifdef USE_OLD_ENUM
	enum PROGRAM_RUN_STATE
	{
		UNKNOWN			//알 수 없는 상태입니다.
		, INITIALIZE	//초기화 중입니다.
		, NORMAL		//정상 실행중입니다.
		, WARNING		//문제가 발생할 수 있습니다.
		, EXCEPTION		//예외가 발생했습니다.
		, EXIT			//종료중입니다.
	};
#else
	enum class PROGRAM_RUN_STATE
	{
		UNKNOWN			//알 수 없는 상태입니다.
		, INITIALIZE	//초기화 중입니다.
		, NORMAL		//정상 실행중입니다.
		, WARNING		//문제가 발생할 수 있습니다.
		, EXCEPTION		//예외가 발생했습니다.
		, EXIT			//종료중입니다.
	};
#endif

	enum class PROGRAM_WORK_STATE
	{
		UNKNOWN			//알 수 없는 상태입니다.
		, INITIALIZE	//초기화 중입니다.
		, IDLE			//대기 상태입니다.
		, CONSOLIN		//콘솔에서 입력을 받습니다.
		, CONSOLOUT		//콘솔에 데이터를 작성합니다.
		, FILEIN		//파일을 읽어들입니다.
		, FILEOUT		//파일로 데이터를 저장합니다.
		, TASK_CREATE	//작업을 생성하고 있습니다.
		, TASK_EDIT		//작업을 수정하고 있습니다.
		, TASK_DELETE	//작업을 삭제하고 있습니다.
		, EXIT			//종료중입니다.
	};

	class Status
	{
	public:
		//@@'단일자 구조(Singleton Pattern)'
		//개인적인 방식으로 변형한 구조입니다.
		//일반적으로 GetInstance 안에서 검사를 통해 작업하므로 Initialize_Mgr을 구현하는데
		//여러 문제로 복잡한 검사가 들어갈 때가 있습니다.
		//애초에 문제를 단순하게 해결하기 위해 구분되어 사용합니다.
		static void Initialize_Mgr();
		static Status* GetInstance();
		void Release();
		//~@@'단일자 구조(Singleton Pattern)'

		//프로그램에 문제가 발생하지 않았는지 확인합니다.
		bool CheckProgramRunSanity();

		//현재 프로그램의 실행 상태를 얻어옵니다.
		PROGRAM_RUN_STATE GetProgramRunState();
		//현재 프로그램의 동작 상태를 얻어옵니다.
		PROGRAM_WORK_STATE GetProgramWorkState();

		//프로그램의 실행 상태가 변경되어야 할 때 사용합니다
		//이전 상태를 반환해서 Set한 값이 이전 값과 다를 때 처리를 할 수 있도록 합니다.
		PROGRAM_RUN_STATE SetProgramRunState(PROGRAM_RUN_STATE _CurrentState);

		//프로그램의 동작 상태가 변경되어야 할 때 사용합니다
		//이전 상태를 반환해서 Set한 값이 이전 값과 다를 때 처리를 할 수 있도록 합니다.
		PROGRAM_WORK_STATE SetProgramWorkState(PROGRAM_WORK_STATE _CurrentState);

		//마지막 상태를 기록하는 문자열을 갱신합니다.
		void UpdateLastStateString(const std::wstring& _UpdateString);

	private:
		//@@'단일자 구조(Singleton Pattern)'
		//생성과 삭제를 외부에서 제어할 수 없도록 막아버린 부분입니다.
		explicit Status();

		//'기본 생성자 제거' 키워드로 찾아보시면 설명이 나와있습니다.
		Status(const Status& /*_classObject*/) = delete;
		Status(Status&& /*_classObject*/) = delete;

		~Status();
		//~@@'단일자 구조(Singleton Pattern)'

	public:

	private:
		//'클래스 소속 변수(Class Member Value)' 입니다.
		//Class는 메모리 레이아웃상 vtable / value 의 순으로 정렬되므로, 함수의 아래에 배치하였습니다.
		//어디까지나 제 습관입니다.
		PROGRAM_RUN_STATE m_programRunState;
		PROGRAM_WORK_STATE m_programWorkState;

		//종료될 때 남기고 싶은 정보를 적어두는 문자열입니다.
		std::wstring m_lastStateString;

		//@@'단일자 구조(Singleton Pattern)'
		//프로그램에서 유일하게 존재하는 객체를 선언합니다.
		//클래스 안에 선언하면 클래스 명으로 namespace 효과를 받기 때문에 패턴을 구현할때 동일한 변수명을 사용할 수 있어서 좋습니다.
		//정 클래스 안에 넣기 싫으시다면 외부에 선언하더라도 프로그램 전역에서 딱 하나의 객체만 유지되면 아무 이상이 없다고 생각합니다.
		static Status* m_instance;
		//~@@'단일자 구조(Singleton Pattern)'
	};
}

#endif

/*
* (※주의※)이 내용은 굳이 지금 보지 않으셔도 되어서 별도 주석으로 작성되었습니다.
*	상당히 높은 난이도의 문제이므로 이 문제를 마주하셨을 언젠가 찾아보실만한 부분의 내용을 노트합니다.
* 
* 구현에 사용된 '단일자 구조(Singleton Pattern)'의 안정성 부분에서 필자가 생각하는 가장 최악의 문제는 '프로그램 충돌(Exception / Crash)'를 발생시키는 부분이라고 생각합니다.
* 이 문제는 어디에서도 하나의 객체에 접근되는 문제에서 시작됩니다.
* 
* 윈도우 프로그램은 응답성을 위해 '다중 실행흐름(Multi Threading)' 이라는 방법을 사용한 프로그램을 구성할 때가 있습니다.
*	*'다중 실행흐름'등의 한글 표현은 조금이라도 직관적으로 표현하기 위한 작성자의 발악일 뿐이고 정식 해석이 아니므로 그냥 여기에서만 그렇게 했구나 하고 넘어가주시기 바랍니다.
* 
* 흔히, '윈도우 메세지 처리부'와 '프로그램 기능 처리부' 그리고 '그리기 처리부'를 구분해서 동작시키는데 들어갑니다.
* 여기서 '프로그램 로직'부분은 다른 이유에 의해 더 세밀하게 쪼개지기도 합니다.
* 
* 이는 몇가지 이유에서 이렇게 구분됩니다.
* 
* 1. 키입력과 윈도우에서 보내는 하드웨어 입력이 처리되는 윈도우 메세지가 다른 동작에 의해 막히지 않고
*	 원활하게 수행되어 프로그램에서 '응답없음'을 띄우는 상황을 막기 위함이 있습니다.
* 
* 2. 여러분이 만드는 프로그램이 여러 동작을 수행할 때 사용자의 이용 측면에서 이 부분이 굳이
*	 프로그램을 사용하지 못하게 할 문제가 아니고 조금 늦더라도 언젠가 완료만 되면 문제가 없을 때
*	 상호간에 간섭을 하지 않도록 분리합니다.
* 
* 3. 최종 사용자가 프로그램을 사용할 때 프로그램 그 자체에 문제가 났는지 오해하지 않게 하기 위한 조치 중 하나입니다.
*	 1번 2번이 혼합된 이유로, 고객이 사용할 때 프로그램에 문제가 일어나지 않았다면 화면이 계속 갱신되고 있어야
*	 사용자들이 프로그램에 문제가 있는지 궁금해하며 강제로 종료하지도, 정상 동작을 버그로 제보하지도 않을 것 입니다.
* 
* 위 내용이 어째서 '단일자 구조(Singleton Pattern)'의 문제인가 하면, 일반적으로 OS에 들어가있는 '메모리 보호(Memory Protection)' 에 의한 문제가 있습니다.
* 작성된 Status 객체를 예로 들어, 아래와 같은 상황이 발생할 수 있습니다.
* 
* 조건.
*	윈도우 메세지 처리부, 프로그램 기능 처리부, 그리기 처리부 세 가지 부분에서 '실행흐름'을 나누어 사용하고 있는 프로그램 A가 있을 때.
*	프로그램 A의 '윈도우 메세지 처리부'의 '실행흐름'에서 WM_QUIT(프로그램 종료 메세지)를 처리하면서 State 객체의 CurrentState 값을 Normal에서 EXIT로 변경하는 도중에
*	'그리기 처리부'의 '실행흐름'에서 State 객체의 CurrentState 값을 읽어들여서 지금 프로그램이 종료되지 않아서 새로 그려야 하는지를 확인하고 있는 경우.
*	
* 위와 같은 경우가 발생하면 '그리기 처리부'의 '실행흐름'에는 CurrentState가 Normal인 상태이고, '윈도우 메세지 처리부'에서는 CurrentState가 EXIT가 되어야 하는 상황이 생깁니다.
* 이것은 프로그램에서 '실행흐름'을 관리 할 때의 구조적 문제입니다.
*	이 실행흐름도 주제가 상당히 깊어지므로 궁금하신 분은 '실행흐름 문맥(Thread Context)'이나 '실행흐름 저장소(Thread Local Storage - TLS)', 그리고 '조건부 저장(Cache)'을 키워드로 검색 해 보시면 다양한 자료가 나옵니다.
*   다만, 난이도가 상당합니다 주의 해 주세요.
* 이런 경우에 OS의 '메모리 보호' 기능은 프로그램에서 메모리에 대한 '접근 에러(Access Violation)'가 발생했다는 예외를 출력시킵니다.
* 
* 보안적으로 생각 해 보면, 왜 이것이 에러인지 쉽게 와 닿을 수 있다고 생각합니다.
* 함부로 보여줄 수 없는 값에 대해 접근하고 있을 때,
* '실행흐름'이 다르다고 해서 어떤 실행흐름에서는 '잠금' 상태인 값이 다른 '실행흐름(Thread)'이나 프로그램에서 '해제'가 되어버리는 사태를 막기 위함입니다.
* 이를 '메모리 정합성(Memory consistency)'이라고 합니다.
* 
* 중요한 점은 '메모리가 서로 다른 흐름상에서 서로 다른 값이 되는 경우'가 문제이므로, 읽기 동작에는 문제가 발생하지 않습니다.
* 쓰기 동작이 문제입니다.
*
* 위와 같은 상황을 막기 위해 '잠금(Lock)'을 사용하거나 '잠금 없는 정합성 구조(Lock-Free Pattern)'을 사용해서 구현해야 하는 객체입니다.
* 이 내용은 아직까지도 논의되고 있는 깊은 내용이므로 이런 문제가 있다는 사실만 작성하고 넘어가겠습니다.
* 
* 예제 프로그램에서는 단순한 '단일 실행흐름(Single Threading)' 형식의 프로그램을 만들고 있고
* 필요 이상의 복잡도로 난이도를 올리지 않는 방향으로 예제를 보여드리기 위해 각종 안전장치가 없는 상태입니다.
* 
* 덤으로 구현도 작성자 개인의 방식대로 만든 부분이 있습니다.
* 
* 다른 프로그램에 사용하시려고 하다가 의도하지 않은 문제를 발생시킬 수 있으므로 사용에 주의를 요합니다.
*/