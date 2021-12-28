#include "headers_custom.h"

namespace Manager
{
	//@@'������ ����(Singleton Pattern)'

	//'���� �ɹ� ����(Static Member Value)'�� cpp���� �ʱ�ȭ�� �Ǿ�� �մϴ�.
	//���� ������ ���������� �� 0, NULL, nullptr�� �ʱ�ȭ �� �νô°��� �����ϴ�.
	//Debug������ ������� ���� �Ҵ�Ǵ� ������ �˾Ƽ� 0���� �������ִ� ���� ģ���� ��Ǯ�ٰ�
	//Release������ ����ȭ�� �ʱ�ȭ�� �ȵǴ� �ٶ��� ������ �浹�� �߻��ϱ⵵ �մϴ�.
	//�̴� ���� �����ڰ� �ƴϴ��� '������'�� ����Ҷ� ���� �߿��� ó���Դϴ�.
	Status* Status::m_Instance = nullptr;
	//~@@'������ ����(Singleton Pattern)'

//Public Function
	//@@'������ ����(Singleton Pattern)'
	void Status::Initialize_Mgr()
	{
		//���� ��ü�� m_Instance�� �ùٸ��� ����Ѵٸ� ���α׷� ��ü���� �����ϰ� �����ϴ� �������Դϴ�.
		//�����ڴ� ���α׷� ��ü���� ��ü�� �� �ϳ��θ� ������ �ʿ䰡 �ִ� �����̹Ƿ� �Ҵ��� �� ���� �ִ��� �˻��մϴ�.
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		if (nullptr == m_Instance)
		{
			//������ ����� ���� ���ٸ� ���ο� ��ü�� �Ҵ��մϴ�.
			m_Instance = new Status();
		}
	}

	Status* Status::GetInstance()
	{
		//� ��ġ������ �� �Լ��� ���� ���� �Ҵ�� ������ ��ü�� �����մϴ�.
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		return m_Instance;
	}

	void Status::Release()
	{
		//�Ҵ� �� ���� �������� �����ϴ� �������� ���������μ� �������⼭ �Ҹ� �� �ִ� ������ ���� Ư�������� ����ϴ� �˻��Դϴ�.
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		if (nullptr != m_Instance)
		{
			//�Ҵ� �� ���� �ִٸ� ������ �����մϴ�.
			delete m_Instance;
			//�����ڴ� �����ǰ� ���� �ٸ� ������ �߻��ϱ� ���� m_Instance�� ���� �˻��ϰ� �����ϴµ��ٰ�,
			//�� Release ������ �ùٸ��� ����Ǳ� ���ؼ� �� ��ü �����͸� 0, NULL, nullptr ������ �����س��� �մϴ�.
			m_Instance = nullptr;
		}
	}
	//~@@'������ ����(Singleton Pattern)'

	bool Status::CheckProgramRunSanity()
	{
		//���������� üũ���� �� NORMAL ���°� �ƴ϶�� ������ �ƴ϶�� �����մϴ�.
		//'���� �����帧(Single Thread)' ���������� ������ ó���Դϴ�.
		//'���� �����帧(Multi Thread)' ���������� �ٸ� Thread���� �ٸ� ���¸� ó���� �� �����Ƿ� �Ϻ� ���ܸ� �����ϰų� �ϰ� �ʹٸ� EXIT�� �ƴ���
		//Ȥ�� Ư�� �����ϰ� ���� ���°� �ƴ����� Ȯ���ϴ� �������� �����ؾ��մϴ�.
		return PROGRAM_RUN_STATE::NORMAL == m_programRunState;
	}

	PROGRAM_RUN_STATE Status::GetProgramRunState()
	{
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		return m_programRunState;
	}

	PROGRAM_WORK_STATE Status::GetProgramWorkState()
	{
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		return m_programWorkState;
	}

	PROGRAM_RUN_STATE Status::SetProgramRunState(PROGRAM_RUN_STATE _CurrentState)
	{
		PROGRAM_RUN_STATE prevState = m_programRunState;
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		m_programRunState = _CurrentState;

		return prevState;
	}

	PROGRAM_WORK_STATE Status::SetProgramWorkState(PROGRAM_WORK_STATE _CurrentState)
	{
		PROGRAM_WORK_STATE prevState = m_programWorkState;
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		m_programWorkState = _CurrentState;

		return prevState;
	}

//Private Function
	Status::Status()
		: m_programRunState(PROGRAM_RUN_STATE::INITIALIZE)
		, m_programWorkState(PROGRAM_WORK_STATE::INITIALIZE)
	{
		//�ʿ��� �ʱ�ȭ �۾��� �����ϴ� ��ġ�Դϴ�.

		//�ʱ�ȭ�� ������ �Ϲ� ���·� �����մϴ�.
		SetProgramRunState(PROGRAM_RUN_STATE::NORMAL);
		SetProgramWorkState(PROGRAM_WORK_STATE::IDLE);
	}

	Status::~Status()
	{
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		if (PROGRAM_RUN_STATE::EXIT != SetProgramRunState(PROGRAM_RUN_STATE::EXIT))
		{
			//Manager::Status�� ���α׷��� ���۰� ���� �Բ��ϰ� ������ �����ϰ� �ֱ� ������ �����ȴٸ� �ٸ� ������ EXIT�� �޾Ҿ�� �ùٸ��ϴ�.
			//EXIT���� �ƴϾ��ٴ� ���� ���� �� ���� �ܰ踦 ��ġ�� �ʾ��� Ȯ���� �����ϴ�. (Ex. EXCEPTION ���� ������ �߻��ؼ� ���α׷��� ������ ����ȴٰų� ��)
			//�⺻������ Status�� Manager�� ���� �ܰ迡�� ���� �������� �����ǵ��� �����մϴ�.
			//�ֳ��ϸ�, �ٸ� ��ü���� ������ �� ������ ���α׷� ���¿� �°� �����ϵ��� �����ϱ� �����Դϴ�.
			//�׷��Ƿ� ������� �����ߴµ� PROGRAM_RUN_STATE�� EXIT�� �ƴ϶�� �޸� ������ ���� ���� �˻�� ��ġ�� �ʿ��մϴ�.
			//RUN_STATE�� ���α׷� ��ü�� ���� '���� ó�����(State Machine)'�̹Ƿ� State��ü�� ���� ����ó���� �����մϴ�.

		}

		if (PROGRAM_WORK_STATE::EXIT != SetProgramWorkState(PROGRAM_WORK_STATE::EXIT))
		{
			//Manager::Status�� ���α׷��� ���۰� ���� �Բ��ϰ� ������ �����ϰ� �ֱ� ������ �����ȴٸ� �ٸ� ������ EXIT�� �޾Ҿ�� �ùٸ��ϴ�.
			//EXIT���� �ƴϾ��ٴ� ���� ���� �� ���� �ܰ踦 ��ġ�� �ʾ��� Ȯ���� �����ϴ�. (Ex. EXCEPTION ���� ������ �߻��ؼ� ���α׷��� ������ ����ȴٰų� ��)
			//�⺻������ Status�� Manager�� ���� �ܰ迡�� ���� �������� �����ǵ��� �����մϴ�.
			//�ֳ��ϸ�, �ٸ� ��ü���� ������ �� ������ ���α׷� ���¿� �°� �����ϵ��� �����ϱ� �����Դϴ�.
			//�׷��Ƿ� ������� �����ߴµ� PROGRAM_RUN_STATE�� EXIT�� �ƴ϶�� �޸� ������ ���� ���� �˻�� ��ġ�� �ʿ��մϴ�.
			//WORK_STATE�� ���α׷� ������ ���ۿ� ���� '���� ó�����(State Machine)'�̹Ƿ� State������ ��ü�� ���� ����ó���� �����մϴ�.

		}
	}
}