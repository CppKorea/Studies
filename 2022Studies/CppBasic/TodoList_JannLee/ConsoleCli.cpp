#include "ConsoleCli.h"
#include <iostream>
#include <boost/locale.hpp>
#include <fmt/format.h>

namespace practicalCpp
{
    using std::cout;
    using boost::locale::translate;
    using boost::program_options::variables_map;
    using fmt::format;

    ConsoleCli::ConsoleCli()
    {
        using std::make_pair;
        using std::pair;

        using boost::program_options::options_description;
        commands_ = std::list<Command>
        {
            {
                "help", "h", translate("Print this help message."), options_description(),
                [this](const variables_map&, const options_description&)->pair<int, ConsoleCli::NextAction>
                {
                    cout << translate("Usage: <Command> [<args>]\n\n");

                    cout << translate("Command Options\n");
                    for (const auto& command : commands_)
                    {
                        cout << format("  {:2} | {:10} {}\n", command.shortcut, command.name, command.description);
                    }
                    cout << translate("\nType \"<Command> --help\" to see the details of command usage.\n\n");

                    return make_pair(0, NextAction::WAIT_INPUT);
                }
            },
            {
                "clear", "c", translate("Clear screen."), options_description(),
                [](const variables_map&, const options_description&)->pair<int, ConsoleCli::NextAction>
                {
                    // TODO: 추후 멀티 플랫폼 고려("cls"는 윈도우에서만 동작)
                    system("cls");
                    return make_pair(0, NextAction::WAIT_INPUT);
                }
            },
            {
                "exit", "x", translate("Exit this program."), options_description(),
                [](const variables_map&, const options_description&)->pair<int, ConsoleCli::NextAction>
                {
                   return make_pair(0, NextAction::EXIT);
                }
            },
        };
    }

    // 테스트해본 결과, 현재 환경(Windows10, VS 2019)에서 utf8을 통한 istream 한글 입력이 안됩니다.
    // 그러므로 ansi로 입력받은 문자열을 명시적으로 utf8로 변환합니다.(AnsiToUtf8)
    // TODO: UTF8 입력을 좀더 명확하게 처리할 수 있는 방법을 고민해봐야 합니다.
    // 관련 로직은 Locale.h 생성자에서 일부 설정되는 부분이 있습니다.
    int ConsoleCli::Execute(int /*argc*/, char* /*argv*/[])
    {
        for (std::string commandLine; cout << format("{}>", status_) && std::getline(std::cin, commandLine);)
        {
            std::cin.clear();
            using std::logic_error;
            try
            {
                commandLine = Locale::AnsiToUtf8(commandLine);
                if (auto commandOptions = boost::program_options::split_winmain(commandLine);
                    !commandOptions.empty())
                {
                    auto isCommandFound = false;
                    for (const auto& command : commands_)
                    {
                        if (commandOptions[0] == command.name || commandOptions[0] == command.shortcut)
                        {
                            const auto& options = boost::program_options::command_line_parser({
                                ++commandOptions.begin(), commandOptions.end()
                            }).options(command.options_description).run();
                            variables_map vm;
                            store(options, vm, true);
                            notify(vm);
                            switch (command.notifier(vm, command.options_description).second)
                            {
                            case NextAction::WAIT_INPUT:
                                break;
                            case NextAction::EXIT:
                                return 0;
                            default:
                                throw logic_error(translate("Unknown next action has occured."));
                            };
                            isCommandFound = true;
                            break;
                        }
                    }
                    if (!isCommandFound)
                    {
                        throw logic_error(format(translate("{} is unknown command.").str(), commandOptions[0]));
                    }
                }
                else
                {
                    // 전통적으로 CLI는 아무것도 입력하지 않고 엔터를 입력할 경우, 다음 프롬프트로 넘어갑니다.
                }
            }
            catch (logic_error& error)
            {
                std::cerr << format(translate("ERROR: {}\n\n").str(), error.what());
            }
        }

        return 0;
    }

    void ConsoleCli::AddCommand(const Command& command)
    {
        commands_.push_back(command);
    }

    void ConsoleCli::SetStatus(const std::string& status)
    {
        status_ = status;
    }
}
