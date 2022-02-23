#pragma once
#ifndef PRACTICAL_CPP_TASK_H
#define PRACTICAL_CPP_TASK_H

#include <iostream>
#include <shared_mutex>
#include <string>
#include <fmt/format.h>

namespace practicalCpp
{
    class Task
    {
    public:
        // 신규 작업 상태가 추가될 수도 있음을 감안하여, value range를 넓게 분포시킴
        enum class State : std::uint32_t
        {
            UNKNOWN = 0,
            TODO,
            DOING,
            DONE
        };

        Task() = default;
        Task(const std::string& title, const State& state) noexcept;
        virtual ~Task() = default;

        // Task의 Getter, Setter는 thread safe하지 않음
        std::string GetTitle() const noexcept;
        void SetTitle(const std::string& name) noexcept;

        State GetState() const noexcept;
        void SetState(const State& state) noexcept;

        static Task::State ToState(const std::string& text);
        static std::string ToString(const State& state);

    private:
        std::string title_{ "" };
        State state_{ State::TODO };
    };

    std::istream& operator>>(std::istream& in, Task::State& state);
    std::ostream& operator<<(std::ostream& out, Task::State state);
}

template <>
struct fmt::formatter<practicalCpp::Task::State> : formatter<string_view>
{
    template <typename FormatContext>
    auto format(practicalCpp::Task::State state, FormatContext& ctx)
    {
        return formatter<string_view>::format(practicalCpp::Task::ToString(state), ctx);
    }
};


#endif // PRACTICAL_CPP_TASK_H
