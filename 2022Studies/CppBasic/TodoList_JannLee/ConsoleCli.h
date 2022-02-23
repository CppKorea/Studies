#pragma once
#ifndef PRACTICAL_CPP_CONSOLE_CLI_H
#define PRACTICAL_CPP_CONSOLE_CLI_H

#include <functional>
#include <string>
#include <boost/program_options.hpp>
#include "Locale.h"
#include "UniqueObject.hpp"

namespace practicalCpp
{
    class ConsoleCli : public UniqueObject<ConsoleCli>
    {
    public:
        ConsoleCli();
        virtual ~ConsoleCli() = default;

        int Execute(int argc, char* argv[]);

    protected:
        enum class NextAction
        {
            UNKNOWN = 0,
            WAIT_INPUT,     // 입력 대기
            EXIT,           // 프로그램 종료
        };

        struct Command
        {
            std::string name;
            std::string shortcut;
            std::string description;
            boost::program_options::options_description options_description;
            std::function<std::pair<int, NextAction>(
                const boost::program_options::variables_map&,
                const boost::program_options::options_description&)> notifier;
        };

        template<typename Ret, typename Class, typename Param1, typename Param2>
        std::function<std::pair<int, NextAction> /*Notify*/(
            const boost::program_options::variables_map& /*variables*/,
            const boost::program_options::options_description& /*description*/)> Bind(Ret(Class::* f)(Param1, Param2))
        {
            return std::bind(f, static_cast<Class*>(this), std::placeholders::_1, std::placeholders::_2);
        }

        void AddCommand(const Command& command);
        void SetStatus(const std::string& status);

    private:
        Locale locale_;
        std::list<Command> commands_;
        std::string status_{ "" };
    };
}

#endif // PRACTICAL_CPP_CONSOLE_CLI_H
