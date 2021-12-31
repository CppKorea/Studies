#ifndef STUDY_LOCALIZE_H__
#define STUDY_LOCALIZE_H__

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
	class Study_Localize
	{
	public:

		//@@'������ ����(Singleton Pattern)'
		//�������� ������� ������ �����Դϴ�.
		//�Ϲ������� GetInstance �ȿ��� �˻縦 ���� �۾��ϹǷ� Initialize_Mgr�� �����ϴµ�
		//���� ������ ������ �˻簡 �� ���� �ֽ��ϴ�.
		//���ʿ� ������ �ܼ��ϰ� �ذ��ϱ� ���� ���еǾ� ����մϴ�.
		static void Initialize_Mgr(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName);
		static Study_Localize* GetInstance();
		void Release();
		//~@@'������ ����(Singleton Pattern)'

		//���ڸ� ���ɴϴ�.
		//��ġ�ϴ� Ű�� ���� �� false�� ���ɴϴ�.
		bool GetLocalizeString(const std::wstring& _stringKey, std::wstring& _Result);

	private:
		//@@'������ ����(Singleton Pattern)'
		//������ ������ �ܺο��� ������ �� ������ ���ƹ��� �κ��Դϴ�.
		explicit Study_Localize(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName);

		//'�⺻ ������ ����' Ű����� ã�ƺ��ø� ������ �����ֽ��ϴ�.
		Study_Localize() = delete;
		Study_Localize(const Study_Localize& /*_classObject*/) = delete;
		Study_Localize(Study_Localize&& /*_classObject*/) = delete;

		~Study_Localize();
		//~@@'������ ����(Singleton Pattern)'

	public:


	private:
		std::map<std::wstring, std::wstring> m_stringDataBase;

		//@@'������ ����(Singleton Pattern)'
		//���α׷����� �����ϰ� �����ϴ� ��ü�� �����մϴ�.
		//Ŭ���� �ȿ� �����ϸ� Ŭ���� ������ namespace ȿ���� �ޱ� ������ ������ �����Ҷ� ������ �������� ����� �� �־ �����ϴ�.
		//�� Ŭ���� �ȿ� �ֱ� �����ôٸ� �ܺο� �����ϴ��� ���α׷� �������� �� �ϳ��� ��ü�� �����Ǹ� �ƹ� �̻��� ���ٰ� �����մϴ�.
		static Study_Localize* m_instance;
		//~@@'������ ����(Singleton Pattern)'
	};
}

#endif