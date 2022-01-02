#include "Grouping/headers_custom.h"

namespace Manager
{

}

Manager::Func_Object::Study_Task::Study_Task(std::wstring& _string)
	: m_status(TaskStatus::NONE)
	, m_string(_string)
{
}

Manager::Func_Object::Study_Task::~Study_Task()
{
}

void Manager::Func_Object::Study_Task::SetStatus(TaskStatus _status)
{
	//�Էµ� ������ ���°��� �����մϴ�.
	m_status = _status;
}

void Manager::Func_Object::Study_Task::SetString(const std::wstring& _string)
{
	//�Էµ� ������ ToDo ���ڸ� �ٲߴϴ�.
	m_string = _string;
}

void Manager::Func_Object::Study_Task::GetStatus(std::wstring& _string)
{
	//�Էµ� �Ķ���Ϳ� ���°��� �°� ���ڸ� �����մϴ�.
	switch (m_status)
	{
	case TaskStatus::NONE:
		_string = L"NONE";
		break;
	case TaskStatus::PROGRASS:
		_string = L"PROGRASS";
		break;
	case TaskStatus::DONE:
		_string = L"DONE";
		break;
	default:
		_string = L"UNKNOWN";
		break;
	}
}

void Manager::Func_Object::Study_Task::GetString(std::wstring& _string)
{
	//�Էµ� �Ķ���Ϳ� ToDo ������ �����ϰ� �����մϴ�.
	_string = m_string;
}

void Manager::Func_Object::Study_Task::GetFullData(std::wstring& _string)
{
	//���� ���ǵ� �� �Լ��� ����� ToDo �� �� Row�� ���� ���ڿ��� �ϼ��ؼ� ��ȯ�մϴ�.
	std::wstring StatusStr;
	std::wstring StringStr;

	GetStatus(StatusStr);
	GetString(StringStr);

	_string = L"|" + StatusStr + L"|" + StringStr + L"|";
}
