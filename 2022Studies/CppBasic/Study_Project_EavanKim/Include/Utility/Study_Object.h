#ifndef STUDY_OBJECT_H__
#define STUDY_OBJECT_H__

/*
*
* (�ذ���) ���ٺ� �ڱ�� �ڵ� �ۼ����� ���Ǿ����ϴ�.
* �ڵ� �ۼ��ڰ� �Ǽ��ϴ� �κе��� �������� �������� �ۼ����� ���Ǿ� �ֽ��ϴ�.
* �ڵ� �ۼ��� ���� ����� �����Ͻ��� ���ð� �̷� ������ �ֱ��� ������ �����Ͽ� �ֽʽÿ�.
*
* ���α׷��� ���� ���� ó�� �����ϽŴٸ� ���� Ȯ������ �����ŵ� ������� �����Դϴ�.
*
* Base Object
* ���� �������� ������ Smart Pointer �����Դϴ�.
* ǥ���� ���� Unique_ptr, shared_ptr�� ������� ���ϴ� �����̰ų�
* smart_ptr�� ���� ������ ��ü������ �������� �Ʒ��� ���� �۾��ϴ� ��츦 �� �� �ֽ��ϴ�.
* ������ �ǹ̸� ���� �� �ֵ��� �ܼ��ϰ� �����Ͽ����ϴ�.
* 
* �����ϰ� ����Ϸ��� thread-safe�� Interlocked �� �����ϴ� ������ �����ڸ� ����ϰ�, ������ volatile ���� �� �� �ʿ䰡 �ֽ��ϴ�.
*
*/

namespace Default
{
	//���۷��� ī��Ʈ�� ��� �����Ǿ��°��� ���ڰ� �޶����� �ȵǹǷ�, �ֻ��� ��� ��ü�� �����ϰ� �̰��� �����մϴ�.
	//�����ͷ� �����ϴ� ��ü�� ī��Ʈ�� ��� �����Ƿ�, � ������ ī��Ʈ�� �ٶ󺾴ϴ�.
	class Study_Object
	{
	public:
		explicit Study_Object()
			: m_referenceCount(0)
		{

		}

		//������ �� ���� ������ ��ü�� ����ִ°� �ƴϹǷ� �� �۾��� �����ϴ�.
		virtual ~Study_Object()
		{

		}

		//������ �� ����ؾ��ϴ� ���۷��� ī��Ʈ ���� üũ�Դϴ�.
		int64_t IncreaseReference()
		{
			++m_referenceCount;

			return m_referenceCount;
		}

		//������ �� ����ϴ� ���۷��� ī��Ʈ ����� �Դϴ�.
		int64_t DecreaseReference()
		{
			--m_referenceCount;

			return m_referenceCount;
		}

	private:
		int64_t m_referenceCount = 0;
	};

	//Thread-Safe ó���� �����Ƿ� �׳� ����ϱ⿣ �����մϴ�.
	//�⺻������ Single Threading ���¿����� ����� �����մϴ�.
	template<class T = Study_Object>
	class Study_Ptr
	{
	public:
		explicit Study_ptr(T* _Target)
		{
			Data = _Target;
			Data->IncreaseReference();
		}

		explicit Study_ptr(Study_ptr& _Copy)
			: Data(_Copy.Data)
		{
			Data->IncreaseReference();
		}

		explicit Study_ptr(Study_ptr&& _Copy)
			: Data(_Copy.Data)
		{
			Data->IncreaseReference();
		}

		void Copy(Study_ptr& _Dest, Study_ptr& _Source)
		{
			_Dest.Data = _Source.Data;
			_Dest.Data->IncreaseReference();
		}

		//smart pointer���� 
		T* Get()
		{
			return data;
		}

		//������ �� ���۷��� ī��Ʈ�� üũ �ϰ� �����ϵ��� �մϴ�.
		//�� �� �Լ��� ������ ���Ѿ� �����մϴ�.
		//�� ������ �߻��ϱ� �� ���� ���� ��ü�� �������� �����Ƿ�, �б⸸ �ϴ� ��ü�� �󸶵��� ���� �ּҸ� �ٶ� �� �ֽ��ϴ�.
		//'���� �����帧(Multi-Threading)' ���α׷������� �ſ� �����ϹǷ� ���� ������ġ�� �ʿ��մϴ�.
		void Release()
		{
			int64_t ReferenceCount = data->DecreaseReference();

			if (!ReferenceCount)
			{
				delete data;
				data = nullptr;
			}
		}

	private:
		T* data = nullptr;
	};
}

#endif