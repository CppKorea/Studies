#ifndef STUDY_OBJECT_H__
#define STUDY_OBJECT_H__

/*
*
* (※경고※) 무근본 자기류 코드 작성법이 사용되었습니다.
* 코드 작성자가 실수하는 부분들을 막으려는 개인적인 작성법이 사용되어 있습니다.
* 코드 작성에 대한 방법은 참조하시지 마시고 이런 생각이 있구나 정도만 참고하여 주십시오.
*
* 프로그램에 대해 완전 처음 도전하신다면 굳이 확인하지 않으셔도 상관없는 내용입니다.
*
* Base Object
* 가장 고전적인 형태의 Smart Pointer 구현입니다.
* 표준이 낮아 Unique_ptr, shared_ptr을 사용하지 못하던 시절이거나
* smart_ptr의 구현 문제로 자체적으로 만들을때 아래와 같이 작업하는 경우를 볼 수 있습니다.
* 구현을 의미만 보실 수 있도록 단순하게 구현하였습니다.
* 
* 안전하게 사용하려면 thread-safe한 Interlocked 로 시작하는 증감소 연산자를 사용하고, 변수를 volatile 선언 해 줄 필요가 있습니다.
*
*/

namespace Default
{
	//레퍼런스 카운트가 어디서 생성되었는가로 숫자가 달라지면 안되므로, 최상위 상속 객체를 지정하고 이곳에 저장합니다.
	//포인터로 접근하는 객체가 카운트를 들고 있으므로, 어떤 때에도 같은 카운트를 바라봅니다.
	class Study_Object
	{
	public:
		//생성과 함께 카운트를 초기화 합니다.
		explicit Study_Object()
			: m_referenceCount(0)
		{

		}

		//삭제될 때 딱히 포인터 객체를 들고있는건 아니므로 별 작업이 없습니다.
		//virtual이 붙은 이유는 상속관계인 대상이 있을 예정이므로 올바르게 소멸자가 순서대로 불리도록 조치된 내용입니다.
		virtual ~Study_Object()
		{

		}

		//참조될 때 사용해야하는 레퍼런스 카운트 증가 체크입니다.
		int64_t IncreaseReference()
		{
			++m_referenceCount;

			return m_referenceCount;
		}

		//해제될 때 사용하는 레퍼런스 카운트 감쇄기 입니다.
		int64_t DecreaseReference()
		{
			--m_referenceCount;

			return m_referenceCount;
		}

	private:
		int64_t m_referenceCount = 0;
	};

	//Thread-Safe 처리가 없으므로 그냥 사용하기엔 위험합니다.
	//기본적으로 Single Threading 상태에서의 사용을 가정합니다.
	template<class T = Study_Object>
	class Study_Ptr
	{
	public:
		//생성하면서 Reference를 증가시켜야 원본이 삭제될 때 올바르게 0으로 카운트 됩니다.
		Study_Ptr(T* _Target)
			: data(_Target)
		{
			data->IncreaseReference();
		}

		//복사는 다른데서 이 포인터를 사용한다는 말이므로 참조를 증가시킵니다.
		Study_Ptr(Study_Ptr& _Copy)
			: data(_Copy.data)
		{
			data->IncreaseReference();
		}

		//복사는 다른데서 이 포인터를 사용한다는 말이므로 참조를 증가시킵니다.
		Study_Ptr(Study_Ptr&& _Copy)
			: data(_Copy.data)
		{
			data->IncreaseReference();
		}

		~Study_Ptr()
		{
			Release();
		}

		//복사는 다른데서 이 포인터를 사용한다는 말이므로 참조를 증가시킵니다.
		void Copy(Study_Ptr& _Dest, Study_Ptr& _Source)
		{
			_Dest.data = _Source.data;
			_Dest.data->IncreaseReference();
		}

		//함수 동작에 필요해서 추가 작성되었습니다.
		Default::Study_Ptr<T>& operator =(const Default::Study_Ptr<T>& _Check)
		{
			this->data = _Check.data;
			this->data->IncreaseReference();

			return *this;
		}

		//smart pointer에서 Get과 동일한 용법입니다.
		//사실 이걸로 포인터를 가져가서 사용하면 위험하므로 포인터를 복제하지 말고 Get으로 쓰자마자 바로 버려야합니다.
		T* Get()
		{
			return data;
		}

		//해제할 때 레퍼런스 카운트를 체크 하고 삭제하도록 합니다.
		//꼭 이 함수로 해제를 시켜야 안전합니다.
		//이 해제가 발생하기 전 까지 원본 객체가 해제되지 않으므로, 읽기만 하는 객체는 얼마든지 같은 주소를 바라볼 수 있습니다.
		//'다중 실행흐름(Multi-Threading)' 프로그램에서는 매우 위험하므로 여러 안전조치가 필요합니다.
		void Release()
		{
			//참조 카운트를 감소시키고 마지막 값을 저장합니다.
			int64_t ReferenceCount = data->DecreaseReference();

			//혹시 마지막 값이 0이면 대상을 삭제합니다.
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