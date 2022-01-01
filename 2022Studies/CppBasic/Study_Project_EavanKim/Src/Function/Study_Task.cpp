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
	m_status = _status;
}

void Manager::Func_Object::Study_Task::SetString(const std::wstring& _string)
{
	m_string = _string;
}

void Manager::Func_Object::Study_Task::GetStatus(std::wstring& _string)
{
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
	_string = m_string;
}

void Manager::Func_Object::Study_Task::GetFullData(std::wstring& _string)
{
	std::wstring StatusStr;
	std::wstring StringStr;

	GetStatus(StatusStr);
	GetString(StringStr);

	_string = L"|" + StatusStr + L"|" + StringStr + L"|";
}
