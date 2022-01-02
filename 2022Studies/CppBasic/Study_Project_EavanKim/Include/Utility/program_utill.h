#ifndef	PROGRAM_UTILL_H__
#define PROGRAM_UTILL_H__

namespace Manager
{
	//���� ���� ��ü�� �� ���� �ʱ�ȭ �ϴ� �Լ��Դϴ�.
	static void Initialize()
	{
		//���α׷� ���� ��θ� �����ͼ� ������ �о���� �ʿ䰡 �ִ� ����� �ش� ��ηκ��� ������ �о���Դϴ�.
		TCHAR programpath[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, programpath);

		Status::Initialize_Mgr();
		Study_Localize::Initialize_Mgr(programpath, L"Resource\\Localize_En");
		//Study_Localize::Initialize_Mgr(programpath, L"Resource\\Localize_Ko");
	}

	//���� ���� ��ü�� �� ���� ���� �ϴ� �Լ��Դϴ�.
	static void Release()
	{
		//������ �ʱ�ȭ�� �������� �ϴ����� �����մϴ�.
		//�ֳ��ϸ�, ���߿� �ʱ�ȭ �� ���� ���� �ʱ�ȭ �� ��� ���� ���Ӽ��� ���� �� �ֱ� �����Դϴ�.
		Study_Localize* LocalizeMgr = Study_Localize::GetInstance();
		if(LocalizeMgr)
			LocalizeMgr->Release();
		Status* StatusMgr = Status::GetInstance();
		if(StatusMgr)
			StatusMgr->Release();
	}
}

#endif