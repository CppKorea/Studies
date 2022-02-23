#include "Task.h"

namespace practicalCpp
{
    using std::ios_base;
    using std::istream;
    using std::ostream;
    using std::string;

    Task::Task(const std::string& title, const State& state) noexcept:
        title_{ title },
        state_{ state }
    {
    }

    std::string Task::GetTitle() const noexcept
    {
        return title_;
    }

    void Task::SetTitle(const std::string& title) noexcept
    {
        title_ = title;
    }

    Task::State Task::GetState() const noexcept
    {
        return state_;
    }

    void Task::SetState(const Task::State& state) noexcept
    {
        state_ = state;
    }

    Task::State Task::ToState(const std::string& text)
    {
        Task::State state;

        if (text == "todo")
            state = Task::State::TODO;
        else if (text == "doing")
            state = Task::State::DOING;
        else if (text == "done")
            state = Task::State::DONE;
        else
            state = Task::State::UNKNOWN;

        return state;
    }

    string Task::ToString(const Task::State& state)
    {
        string stateName;

        switch (state)
        {
        case Task::State::TODO:
            stateName = "todo";
            break;
        case Task::State::DOING:
            stateName = "doing";
            break;
        case Task::State::DONE:
            stateName = "done";
            break;
        case Task::State::UNKNOWN:
        default:
            stateName = "unknown";
            break;
        }

        return stateName;
    }

    istream& operator>>(istream& in, Task::State& state)
    {
        string token;
        in >> token;
        state = Task::ToState(token);
        return in;
    }

    ostream& operator<<(ostream& out, Task::State state)
    {
        return out << Task::ToString(state);
    }
}