#include "Study_Status.h"

namespace Manager
{
	//@@'������ ����(Singleton Pattern)'
	Status* Status::m_Instance = nullptr;
	//~@@'������ ����(Singleton Pattern)'

//Public Function
	//@@'������ ����(Singleton Pattern)'
	void Status::Initialize_Mgr()
	{
		if (nullptr == m_Instance)
		{
			m_Instance = new Status();
		}
	}

	Status* Status::GetInstance()
	{
		return m_Instance;
	}

	void Status::Release()
	{
		if (nullptr != m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	//~@@'������ ����(Singleton Pattern)'

	bool Status::CheckNormalState()
	{
		return PROGRAM_STATE::NORMAL == m_programState;
	}

	PROGRAM_STATE Status::SetProgramState(PROGRAM_STATE _CurrentState)
	{
		PROGRAM_STATE prevState = m_programState;
		m_programState = _CurrentState;

		return prevState;
	}

//Private Function
	Status::Status()
		: m_programState(PROGRAM_STATE::INITIALIZE)
	{
	}

	Status::~Status()
	{
	}
}