#ifndef	PROGRAM_UTILL_H__
#define PROGRAM_UTILL_H__

namespace Manager
{
	//전역 관리 객체를 한 번에 초기화 하는 함수입니다.
	static void Initialize()
	{
		//프로그램 실행 경로를 가져와서 파일을 읽어들일 필요가 있는 대상은 해당 경로로부터 정보를 읽어들입니다.
		TCHAR programpath[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, programpath);

		Status::Initialize_Mgr();
		Study_Localize::Initialize_Mgr(programpath, L"Resource\\Localize_En");
		//Study_Localize::Initialize_Mgr(programpath, L"Resource\\Localize_Ko");
	}

	//전역 관리 객체를 한 번에 해제 하는 함수입니다.
	static void Release()
	{
		//해제는 초기화의 역순으로 하는편이 안전합니다.
		//왜냐하면, 나중에 초기화 될 수록 먼저 초기화 된 대상에 대해 종속성을 가질 수 있기 때문입니다.
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		if(LocalizeMgr)
			LocalizeMgr->Release();
		Status* StatusMgr = Status::GetInstance();
		if(StatusMgr)
			StatusMgr->Release();
	}
}

#endif