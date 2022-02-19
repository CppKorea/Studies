#ifndef STUDY_FUNCTIONMGR_H__
#define STUDY_FUNCTIONMGR_H__

/*
*
* (�ذ���) ���ٺ� �ڱ�� �ڵ� �ۼ����� ���Ǿ����ϴ�.
* �ڵ� �ۼ��ڰ� �Ǽ��ϴ� �κе��� �������� �������� �ۼ����� ���Ǿ� �ֽ��ϴ�.
* �ڵ� �ۼ��� ���� ����� �����Ͻ��� ���ð� �̷� ������ �ֱ��� ������ �����Ͽ� �ֽʽÿ�.
*
* ���α׷��� ���� ���� ó�� �����ϽŴٸ� ���� Ȯ������ �����ŵ� ������� �����Դϴ�.
*
* Localize Manager
* ���α׷����� ���������� ��µǴ� ���ڰ� ���� ���ڿ� ���� ��/�� ��ȯ�� �ǵ��� ��ġ�մϴ�.
* std::exception�� �⺻������ char*�� �ٷ�Ƿ�, Unicode�� �´� ������ ����� �� �ִ� ���� ��ü�� �ϳ� �߰��Ͽ����ϴ�.
*
* ���α׷� �Ը������� �������� �ſ� ������ ����Դϴ�.
* �ܼ��� �̷� ������ �ε����� �� �̷� ���� ���̽��� �۾��Ͻ� �� �ִ� ���� �����Դϴ�.
*
*/

namespace Manager
{
	//���ǻ���
	//result�� parameter�� �迭 �����͸� �Ѱܼ��� �ȵ˴ϴ�.
	//���� ������ ����� ����� ���� �Ҹ����� delete�� �迭 ������ ����� ������� ��ġ�ų�
	//����ϴ� ����� ������ ����ü�� �����ؼ� ����ü�� ������ �� �迭�� ó���ϴ� �� �Դϴ�.
	struct Function_Parameter_Result
	{
		Function_Parameter_Result(std::wstring _key, void* _result = nullptr, void* _parameter = nullptr)
			: key(_key)
			, parameter(_parameter)
			, result(_result)
		{

		}

		~Function_Parameter_Result()
		{
			if (parameter)
				delete parameter;
			if (result)
				delete result;
		}

		std::wstring key;
		void* parameter;
		void* result;
	};

	struct Function_Struct
	{
		Function_Struct(std::wstring _key, void(*_function)(Function_Parameter_Result*))
			: key(_key)
			, function(_function)
		{

		}

		//�Լ� �����ʹ� ���α׷� ���� �� Code������ �ԽõǴ� �Լ��� ��ġ�� ����ϴ� �� �Դϴ�.
		//������ �� �������� �ʵ��� �����մϴ�.
		~Function_Struct()
		{
			function = nullptr;
		}

		void Do(Function_Parameter_Result* _result)
		{
			function(_result);
		}

		std::wstring key;
		void(*function)(Function_Parameter_Result*);
	};

	class Study_FunctionMgr
	{
	public:

		//@@'������ ����(Singleton Pattern)'
		//�������� ������� ������ �����Դϴ�.
		//�Ϲ������� GetInstance �ȿ��� �˻縦 ���� �۾��ϹǷ� Initialize_Mgr�� �����ϴµ�
		//���� ������ ������ �˻簡 �� ���� �ֽ��ϴ�.
		//���ʿ� ������ �ܼ��ϰ� �ذ��ϱ� ���� ���еǾ� ����մϴ�.
		static void Initialize_Mgr();
		static Study_FunctionMgr* GetInstance();
		void Release();
		//~@@'������ ����(Singleton Pattern)'

		void AddFunction(Function_Struct&);
		void RemoveFunction(std::wstring);
		void Do(Function_Parameter_Result*);

	private:
		//@@'������ ����(Singleton Pattern)'
		//������ ������ �ܺο��� ������ �� ������ ���ƹ��� �κ��Դϴ�.
		explicit Study_FunctionMgr();

		//'�⺻ ������ ����' Ű����� ã�ƺ��ø� ������ �����ֽ��ϴ�.
		Study_FunctionMgr(const Study_FunctionMgr& /*_classObject*/) = delete;
		Study_FunctionMgr(Study_FunctionMgr&& /*_classObject*/) = delete;

		~Study_FunctionMgr();
		//~@@'������ ����(Singleton Pattern)'

	public:


	private:
		std::map<std::wstring, Function_Struct> m_FunctionBase;

		//@@'������ ����(Singleton Pattern)'
		//���α׷����� �����ϰ� �����ϴ� ��ü�� �����մϴ�.
		//Ŭ���� �ȿ� �����ϸ� Ŭ���� ������ namespace ȿ���� �ޱ� ������ ������ �����Ҷ� ������ �������� ����� �� �־ �����ϴ�.
		//�� Ŭ���� �ȿ� �ֱ� �����ôٸ� �ܺο� �����ϴ��� ���α׷� �������� �� �ϳ��� ��ü�� �����Ǹ� �ƹ� �̻��� ���ٰ� �����մϴ�.
		static Study_FunctionMgr* m_instance;
		//~@@'������ ����(Singleton Pattern)'
	};
}

#endif