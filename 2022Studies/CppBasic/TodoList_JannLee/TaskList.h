#pragma once
#ifndef PRACTICAL_CPP_TASK_LIST_H
#define PRACTICAL_CPP_TASK_LIST_H

#include <filesystem>
#include <functional>
#include <map>
#include <shared_mutex>
#include "UniqueObject.hpp"
#include "Task.h"


namespace practicalCpp
{
    class TaskList : public UniqueObject<TaskList>
    {
    public:
        TaskList();
        virtual ~TaskList();

        int64_t AddTask(const std::string& title, const Task::State& state);
        void RemoveTask(const int64_t id);
        Task GetTask(const int64_t id);
        void UpdateTask(const int64_t id, const Task& task);

        void Enumerate(const std::function<void(const int64_t, const Task&)>& visit);

        void Clear();
        void Save(const std::filesystem::path& path);
        void Load(const std::filesystem::path& path);

    private:
        // int64_t 최대 값은 9,223,372,036,854,775,807
        // 그러므로 초당 1개씩 신규 task를 만든다 하더라도, 292,471,208,677년 동안 overflow는 발생 안함
        int64_t lastId_{ 0 };
        std::map<int64_t, Task> tasks_;

        std::shared_mutex mutex_;
    };
}

#endif // PRACTICAL_CPP_TASK_LIST_H
