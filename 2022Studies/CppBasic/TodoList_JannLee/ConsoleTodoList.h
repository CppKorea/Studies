#pragma once
#ifndef PRACTICAL_CPP_CONSOLE_TODO_LIST_H
#define PRACTICAL_CPP_CONSOLE_TODO_LIST_H

#include <filesystem>
#include <boost/program_options.hpp>
#include "ConsoleCli.h"


namespace practicalCpp
{
    class TaskList;

    class ConsoleTodoList final : public ConsoleCli
    {
    public:
        explicit ConsoleTodoList(TaskList& taskList);
        virtual ~ConsoleTodoList() = default;

    private:
        TaskList& taskList_;
        std::filesystem::path filePath_ = { ".\\new" }; 
    };
}

#endif // PRACTICAL_CPP_CONSOLE_TODO_LIST_H
