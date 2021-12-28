#ifndef	PROGRAM_UTILL_H__
#define PROGRAM_UTILL_H__

namespace Manager
{
	static void Initialize()
	{
		Status::Initialize_Mgr();
	}

	static void Release()
	{
		Status::GetInstance()->Release();
	}
}

#endif