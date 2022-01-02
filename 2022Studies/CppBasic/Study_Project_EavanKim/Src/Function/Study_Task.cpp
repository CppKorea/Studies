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
	//입력된 값으로 상태값을 변경합니다.
	m_status = _status;
}

void Manager::Func_Object::Study_Task::SetString(const std::wstring& _string)
{
	//입력된 값으로 ToDo 글자를 바꿉니다.
	m_string = _string;
}

void Manager::Func_Object::Study_Task::GetStatus(std::wstring& _string)
{
	//입력된 파라메터에 상태값에 맞게 문자를 저장합니다.
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
	//입력된 파라메터에 ToDo 내용을 저장하고 종료합니다.
	_string = m_string;
}

void Manager::Func_Object::Study_Task::GetFullData(std::wstring& _string)
{
	//위에 정의된 두 함수를 사용해 ToDo 한 개 Row에 대한 문자열을 완성해서 반환합니다.
	std::wstring StatusStr;
	std::wstring StringStr;

	GetStatus(StatusStr);
	GetString(StringStr);

	_string = L"|" + StatusStr + L"|" + StringStr + L"|";
}
