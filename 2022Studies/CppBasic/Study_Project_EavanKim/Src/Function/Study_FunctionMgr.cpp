#include "Grouping/headers_custom.h"

namespace Manager
{
	Study_FunctionMgr* Study_FunctionMgr::m_instance = nullptr;

	void Study_FunctionMgr::Initialize_Mgr()
	{
		if (!m_instance)
			m_instance = new Study_FunctionMgr();
	}

	Study_FunctionMgr* Study_FunctionMgr::GetInstance()
	{
		return m_instance;
	}

	void Study_FunctionMgr::Release()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	void Study_FunctionMgr::AddFunction(Function_Struct& _newFunction)
	{
		std::map<std::wstring, Function_Struct>::iterator End = m_FunctionBase.end();
		std::map<std::wstring, Function_Struct>::iterator Find = m_FunctionBase.find(_newFunction.key);
		if (End == Find)
		{
			m_FunctionBase.insert(std::make_pair(_newFunction.key, _newFunction));
		}
		else
		{
			//에러 처리
		}
	}

	void Study_FunctionMgr::RemoveFunction(std::wstring _key)
	{
		m_FunctionBase.erase(_key);
#if ERASE_CHECK_ENABLE
		std::map<std::wstring, Function_Struct>::iterator End = m_FunctionBase.end();
		std::map<std::wstring, Function_Struct>::iterator Find = m_FunctionBase.find(_key);
		if (End == Find)
		{
			//잘 삭제됨
		}
		else
		{
			//에러 처리
		}
#endif
	}

	void Study_FunctionMgr::Do(Function_Parameter_Result* _result)
	{
		std::map<std::wstring, Function_Struct>::iterator End = m_FunctionBase.end();
		std::map<std::wstring, Function_Struct>::iterator Find = m_FunctionBase.find(_result->key);
		if (End != Find)
		{
			Find->second.Do(_result);
		}
		else
		{
			//에러 처리
		}
	}

	Study_FunctionMgr::Study_FunctionMgr()
	{
		m_FunctionBase.clear();
	}

	Study_FunctionMgr::~Study_FunctionMgr()
	{
		m_FunctionBase.clear();
	}

}
