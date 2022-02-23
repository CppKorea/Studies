#pragma once
#ifndef PRACTICAL_CPP_UNIQUE_OBJECT_HPP
#define PRACTICAL_CPP_UNIQUE_OBJECT_HPP

#include <atomic>
#include <exception>

namespace practicalCpp
{
    // 단일 인스턴스(오브젝트)로 강제화하는 클래스입니다.
    // 중복 생성 시 exception을 유발합니다.
    // 템플릿인 이유: 타입에 따라 컴파일 타임에 정적 멤버 변수를 생성하도록 하기 위함입니다.
    template<typename T> class UniqueObject
    {
    public:
        UniqueObject()
        {
            bool expectedValue{ false };

            if (!isCreated_.compare_exchange_strong(expectedValue, true))
            {
                // TODO: Exception throw 시 어떤 객제가 중복 생성되었는지 전달할 수 있는 방법을 고민해봐야 합니다.
                throw std::exception("Unique object was already created");
            }
        }

        virtual ~UniqueObject()
        {
            isCreated_.exchange(false);
        }

        UniqueObject(const UniqueObject&) = delete;
        UniqueObject& operator=(const UniqueObject&) = delete;

    private:
        static std::atomic_bool isCreated_;
    };

    template<typename T>
    std::atomic_bool UniqueObject<T>::isCreated_{ false };
} // namespace practicalCpp

#endif // PRACTICAL_CPP_UNIQUE_OBJECT_HPP
