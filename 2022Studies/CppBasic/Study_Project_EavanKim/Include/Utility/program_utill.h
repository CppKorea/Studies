#ifndef	PROGRAM_UTILL_H__
#define PROGRAM_UTILL_H__

namespace Manager
{
	static void Initialize()
	{
		TCHAR programpath[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, programpath);

		Status::Initialize_Mgr();
		Study_Localize::Initialize_Mgr(programpath, L"Localize_Ko");
	}

	static void Release()
	{
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		if(LocalizeMgr)
			LocalizeMgr->Release();
		Status* StatusMgr = Status::GetInstance();
		if(StatusMgr)
			StatusMgr->Release();
	}
}

#endif