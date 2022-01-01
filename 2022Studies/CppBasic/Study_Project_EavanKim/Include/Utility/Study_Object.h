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
	//�����ͷ� �����ϴ� ��ü�� ī��Ʈ�� ��� �����Ƿ�, � ������ ���� ī��Ʈ�� �ٶ󺾴ϴ�.
	class Study_Object
	{
	public:
		//������ �Բ� ī��Ʈ�� �ʱ�ȭ �մϴ�.
		explicit Study_Object()
			: m_referenceCount(0)
		{

		}

		//������ �� ���� ������ ��ü�� ����ִ°� �ƴϹǷ� �� �۾��� �����ϴ�.
		//virtual�� ���� ������ ��Ӱ����� ����� ���� �����̹Ƿ� �ùٸ��� �Ҹ��ڰ� ������� �Ҹ����� ��ġ�� �����Դϴ�.
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
		//�����ϸ鼭 Reference�� �������Ѿ� ������ ������ �� �ùٸ��� 0���� ī��Ʈ �˴ϴ�.
		Study_Ptr(T* _Target)
			: data(_Target)
		{
			data->IncreaseReference();
		}

		//����� �ٸ����� �� �����͸� ����Ѵٴ� ���̹Ƿ� ������ ������ŵ�ϴ�.
		Study_Ptr(Study_Ptr& _Copy)
			: data(_Copy.data)
		{
			data->IncreaseReference();
		}

		//����� �ٸ����� �� �����͸� ����Ѵٴ� ���̹Ƿ� ������ ������ŵ�ϴ�.
		Study_Ptr(Study_Ptr&& _Copy)
			: data(_Copy.data)
		{
			data->IncreaseReference();
		}

		//����� �ٸ����� �� �����͸� ����Ѵٴ� ���̹Ƿ� ������ ������ŵ�ϴ�.
		void Copy(Study_Ptr& _Dest, Study_Ptr& _Source)
		{
			_Dest.data = _Source.data;
			_Dest.data->IncreaseReference();
		}

		Default::Study_Ptr<T>& operator =(const Default::Study_Ptr<T>& _Check)
		{
			this->data = _Check.data;
			this->data->IncreaseReference();

			return *this;
		}

		//smart pointer���� Get�� ������ ����Դϴ�.
		//��� �̰ɷ� �����͸� �������� ����ϸ� �����ϹǷ� �����͸� �������� ���� Get���� ���ڸ��� �ٷ� �������մϴ�.
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
			//���� ī��Ʈ�� ���ҽ�Ű�� ������ ���� �����մϴ�.
			int64_t ReferenceCount = data->DecreaseReference();

			//Ȥ�� ������ ���� 0�̸� ����� �����մϴ�.
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