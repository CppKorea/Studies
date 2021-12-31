#include "Grouping/headers_custom.h"

namespace Manager
{
	//@@'������ ����(Singleton Pattern)'

	//'���� �ɹ� ����(Static Member Value)'�� cpp���� �ʱ�ȭ�� �Ǿ�� �մϴ�.
	//���� ������ ���������� �� 0, NULL, nullptr�� �ʱ�ȭ �� �νô°��� �����ϴ�.
	//Debug������ ������� ���� �Ҵ�Ǵ� ������ �˾Ƽ� 0���� �������ִ� ���� ģ���� ��Ǯ�ٰ�
	//Release������ ����ȭ�� �ʱ�ȭ�� �ȵǴ� �ٶ��� ������ �浹�� �߻��ϱ⵵ �մϴ�.
	//�̴� ���� �����ڰ� �ƴϴ��� '������'�� ����Ҷ� ���� �߿��� ó���Դϴ�.
	Study_Localize* Study_Localize::m_instance = nullptr;
	//~@@'������ ����(Singleton Pattern)'

//Public Function
	//@@'������ ����(Singleton Pattern)'
	void Study_Localize::Initialize_Mgr(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName)
	{
		//���� ��ü�� m_Instance�� �ùٸ��� ����Ѵٸ� ���α׷� ��ü���� �����ϰ� �����ϴ� �������Դϴ�.
		//�����ڴ� ���α׷� ��ü���� ��ü�� �� �ϳ��θ� ������ �ʿ䰡 �ִ� �����̹Ƿ� �Ҵ��� �� ���� �ִ��� �˻��մϴ�.
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		if (nullptr == m_instance)
		{
			//������ ����� ���� ���ٸ� ���ο� ��ü�� �Ҵ��մϴ�.
			m_instance = new Study_Localize(_LocaleStringFilePath, _LocaleStringFileName);
		}
	}

	Study_Localize* Study_Localize::GetInstance()
	{
		//� ��ġ������ �� �Լ��� ���� ���� �Ҵ�� ������ ��ü�� �����մϴ�.
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		return m_instance;
	}

	void Study_Localize::Release()
	{
		//�Ҵ� �� ���� �������� �����ϴ� �������� ���������μ� �������⼭ �Ҹ� �� �ִ� ������ ���� Ư�������� ����ϴ� �˻��Դϴ�.
		//�� ������ ��� �ϴ��� ������ ������ ��찡 �߻��ϴ� ��� �� �ϳ��Դϴ�.
		if (nullptr != m_instance)
		{
			//�Ҵ� �� ���� �ִٸ� ������ �����մϴ�.
			delete m_instance;
			//�����ڴ� �����ǰ� ���� �ٸ� ������ �߻��ϱ� ���� m_Instance�� ���� �˻��ϰ� �����ϴµ��ٰ�,
			//�� Release ������ �ùٸ��� ����Ǳ� ���ؼ� �� ��ü �����͸� 0, NULL, nullptr ������ �����س��� �մϴ�.
			m_instance = nullptr;
		}
	}
	//~@@'������ ����(Singleton Pattern)'

	bool Study_Localize::GetLocalizeString(const std::wstring& _stringKey, std::wstring& _Result)
	{
		//�⺻������ �����ϴ� �� �ϳ��� ���̽��� �����ϸ� ��� ���з� ó���ϵ��� �ʱ�ȭ �մϴ�.
		bool Result = false;

		//�̸� �غ��� �����̳ʿ��� Ű�� ����Ͽ� �����͸� �˻��մϴ�.
		std::map<std::wstring, std::wstring>::const_iterator Target = m_stringDataBase.find(_stringKey);

		//����Ǿ����� �˻��մϴ�.
		//Map�� find����� �����Ͱ� ���ٸ� iteration ��ȸ�� ������ ���������Ƿ�, end�� ��ġ�ϴ� ��� �����Ͱ� ���� ��Ȳ�Դϴ�.
		if (Target != m_stringDataBase.end())
		{
			//ã�Ƴ� �����͸� ��ȯ���� �ư� ������� �������� ó���մϴ�.
			_Result = Target->second;
			Result = true;
		}
		else
		{
			//ã�Ƴ� �����Ͱ� ������ ���α׷� ��ü�� �����ϴµ� ������ ������ �� ���ڸ� ǥ���ϴ� ������ ���ڸ� ��ȯ���� �ƽ��ϴ�.
			//���� ����� �α׷� ����� ���������ϴ�.
			_Result = L"####";
			std::wstring CreateErrorMessage(L"!!!Cannot Find String Data!!! | Key : " + _stringKey);
			OutputDebugStringW(CreateErrorMessage.c_str());
		}

		return Result;
	}

	Study_Localize::Study_Localize(const std::wstring& _LocaleStringFilePath, const std::wstring& _LocaleStringFileName)
	{
		//Ȥ�� ������ ���� ���¸� �����ϱ� ���� �Ŵ��� �����͸� ���ɴϴ�.
		Status* StatusMgr = Status::GetInstance();

		//���� �޴����� �ʱ�ȭ ���� �ʾҴٸ� ���� ��ü�� ������ �ִٰ� �Ǵ��մϴ�.
		if ( nullptr != StatusMgr )
		{
			//Ȥ�� �̹� ������ �ִ� �������� Ȯ���մϴ�.
			PROGRAM_RUN_STATE LastStatus = StatusMgr->GetProgramRunState();
			if ((PROGRAM_RUN_STATE::EXCEPTION == LastStatus) || (PROGRAM_RUN_STATE::EXIT == LastStatus))
				return;

			//��ο� ���ϸ����� FullPath�� �������ϴ�.
			std::wstring FullPath = L"";
			FullPath.append(_LocaleStringFilePath);
			FullPath.append(L"\\");
			FullPath.append(_LocaleStringFileName);
			std::wstring ReadResult;
			ReadResult.clear();

			//Localize ���Ͽ��� �����͸� �о���Դϴ�.
			int LoadResult = Study_IO::DataLoad(FullPath, ReadResult);

			//��ȯ �ڵ忡 �°� �۾��մϴ�.
			switch (LoadResult)
			{
			case 0: //����
			{
				//�������� ;�� �������� �˻��մϴ�.
				//�׷��� �ʴٸ� ���۵��� ������ �ִ� ������ �����ͷ� ����մϴ�.
				if (L';' == ReadResult[ReadResult.length() - 1])
				{
					//���Ϸκ��� ������ ���ڿ��� �� �� ���� ��ȸ�մϴ�.
					while (0 != ReadResult.length())
					{
						//; ��ġ�� ã�Ƽ� ���ڿ� ���� ���������� ����ϴ�.
						size_t StringSize = ReadResult.find(L';');
						//Ȥ�� ���ڿ��� �߸��Ǽ� ;�� ã�Ƴ��� ���ϸ� ������ ����մϴ�.
						if (StringSize < ReadResult.length())
						{
							//���ڿ��� �����մϴ�.
							std::wstring SplitString(ReadResult.data(), StringSize, std::allocator<wchar_t>());
							//���ܵ� ���ڿ��� ������ ���ڿ��� �����մϴ�.
							ReadResult = std::wstring(ReadResult, StringSize + 1, std::allocator<wchar_t>());

							//`��ġ�� ã�Ƽ� Key/Value�� ������ ���������� ����ϴ�.
							size_t KeySize = SplitString.find(L'`');
							//Ȥ�� ���ڿ��� �߸��Ǿ `�� ã�Ƴ��� ���ϸ� ������ ����մϴ�.
							if (KeySize < SplitString.length())
							{
								//Key���� �߶���ϴ�.
								std::wstring Key(SplitString.data(), KeySize, std::allocator<wchar_t>());
								//���� ���ڿ����� `�� ���ְ� value�� �����ɴϴ�.
								std::wstring Value(SplitString, KeySize + 1, std::allocator<wchar_t>());
								//�� �ڷḦ ��� �ϳ��� ������ ����� �����մϴ�.
								m_stringDataBase.insert(std::make_pair(Key, Value));
							}
							else
							{
								throw std::exception("Localize Data File Is Corrupted!!!");
							}
						}
						else
						{
							throw std::exception("Localize Data File Is Corrupted!!!");
						}
					}
				}
				else
				{
					throw std::exception("Localize Data File Is Corrupted!!!");
				}
			}
				break;
			case 1:
				//������� �������ε� �ٸ� ���α׷��� �����ϰ� �־ ������ ������ϴ�.
				//StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				//StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				//StatusMgr->UpdateLastStateString(L"[-][Error][Localize Initialize] : File Already Used Another Program");
				break;
			case -1:
				//������ �ִµ� �о���� �� ��°������ �����߽��ϴ�.
				//StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				//StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				//StatusMgr->UpdateLastStateString(L"[-][Error][Localize Initialize] : Cannot Read Localize File");
				break;
			case -2:
				//������ �����ϴ�.
				//StatusMgr->SetProgramRunState(PROGRAM_RUN_STATE::EXCEPTION);
				//StatusMgr->SetProgramWorkState(PROGRAM_WORK_STATE::INITIALIZE);
				//StatusMgr->UpdateLastStateString(L"[-][Error][Localize Initialize] : Cannot Find Localize File");
				break;
			default:
				break;
			}
		}
	}

	Study_Localize::~Study_Localize()
	{
		m_stringDataBase.clear();
	}
}
