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
	class Study_Object
	{
	public:
		//������ �� ��, ������ �ϸ鼭 ������ ����� �����״� ī��Ʈ�� 1 �������ݴϴ�.
		//��, �̸����� �ν��Ͻ��� Heap�� �����ϸ� ī��Ʈ�� ������ �������� ���� �� �ֽ��ϴ�.
		//���� �Ͽ��ּ���.
		explicit Study_Object()
			: m_referenceCount(1)
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


	template<class T = Study_Object>
	class Study_Ptr
	{
	public:

		T* Get()
		{
			data->IncreaseReference();

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