#include "ConsoleTodoList.h"
#include "TaskList.h"
#include <boost/locale.hpp>
#include <fmt/format.h>


// 지워야함
#include <iostream>
namespace practicalCpp
{
    using std::cout;
    using std::istream;
    using std::ios_base;
    using std::make_pair;
    using std::ostream;
    using std::pair;
    using std::string;

    using boost::locale::translate;
    using boost::program_options::options_description;
    using boost::program_options::value;
    using boost::program_options::variables_map;

    using fmt::format;

    ConsoleTodoList::ConsoleTodoList(TaskList& taskList) : taskList_{taskList}
    {
        cout << translate("Console TodoList\n");
        SetStatus(filePath_.u8string());

        options_description addOptions(translate("Add Options"));
        addOptions.add_options()
            ("help,h", translate("Print this help messages for add command.").str().c_str())
            ("title,t", value<string>()->default_value(translate("new task")), translate("Task title").str().c_str())
            ("state,s", value<Task::State>()->default_value(Task::State::TODO), translate("Task state(todo|doing|done)").str().c_str());
        AddCommand({
            "add", "a", translate("Add todo item to the list."), addOptions,
            [this](const variables_map& variables, const options_description& description)
            ->pair<int, ConsoleCli::NextAction>
            {
                if (variables.count("help"))
                {
                    cout << description << "\n";
                }
                else
                {
                    auto title = variables["title"].as<string>();
                    auto state = variables["state"].as<Task::State>();
                    auto id = taskList_.AddTask(title, state);
                    cout << translate("Added new task\n");
                    cout << format("  #{} [{}] {}\n\n", id, state, title);
                }

                SetStatus(filePath_.u8string() + "*");
                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

        options_description removeOptions(translate("Remove Options"));
        removeOptions.add_options()
            ("help,h", translate("Print this help messages for remove command.").str().c_str())
            ("id,i", value<int64_t>()->required(), translate("Task ID to be removed").str().c_str());
        AddCommand({
            "remove", "r", translate("Remove todo item from the list"), removeOptions,
            [this](const variables_map& variables, const options_description& description)
            ->pair<int, ConsoleCli::NextAction>
            {
                if (variables.count("help"))
                {
                    cout << description << "\n";
                }
                else
                {
                    const auto id = variables["id"].as<int64_t>();
                    taskList_.RemoveTask(id);
                    cout << format(translate("Removed #{} task\n\n").str(), id);
                }

                SetStatus(filePath_.u8string() + "*");
                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

        options_description updateOptions(translate("Update Options"));
        updateOptions.add_options()
            ("help,h", translate("Print this help messages for update command.").str().c_str())
            ("id,i", value<int64_t>()->required(), translate("Task ID to be updated").str().c_str())
            ("title,t", value<string>(), translate("Task title to be updated").str().c_str())
            ("state,s", value<Task::State>(), translate("Task state to be updated").str().c_str());
        AddCommand({
            "update", "u", translate("Remove todo item from the list"), updateOptions,
            [this](const variables_map& variables, const options_description& description)
            ->pair<int, ConsoleCli::NextAction>
            {
                if (variables.count("help"))
                {
                    cout << description << "\n";
                }
                else
                {
                    const auto id = variables["id"].as<int64_t>();
                    auto task = taskList_.GetTask(id);

                    if (variables.count("title"))
                    {
                        task.SetTitle(variables["title"].as<string>());
                    }

                    if (variables.count("state"))
                    {
                        task.SetState(variables["state"].as<Task::State>());
                    }

                    taskList_.UpdateTask(id, task);
                    cout << format(translate("updated #{} task\n\n").str(), id);
                    cout << format("  #{} [{}] {}\n\n", id, task.GetState(), task.GetTitle());
                }

                SetStatus(filePath_.u8string() + "*");
                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

        AddCommand({
            "list", "li", translate("List up todo items from the list."), options_description(),
            [this](const variables_map&, const options_description&)
            ->pair<int, ConsoleCli::NextAction>
            {
                taskList_.Enumerate([](const int64_t id, const Task& task)
                {
                    cout << format("  #{} [{}] {}\n", id, task.GetState(), task.GetTitle());
                });
                cout << "\n";
                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

        options_description saveOptions(translate("Save Options"));
        saveOptions.add_options()
            ("help,h", translate("Print this help messages for save command.").str().c_str())
            ("path,p", value<std::filesystem::path>(), translate("File path to be saved").str().c_str());

        AddCommand({
            "save", "s", translate("Save todo list to the file"), saveOptions,
            [this](const variables_map& variables, const options_description& description)
            ->pair<int, ConsoleCli::NextAction>
            {
                if (variables.count("help"))
                {
                    cout << description << "\n";
                }
                else
                {
                    std::filesystem::path path;
                    if (variables.count("path"))
                    {
                        filePath_ = variables["path"].as<std::filesystem::path>();
                    }
                    taskList_.Save(filePath_);
                    SetStatus(filePath_.u8string());
                    cout << format(translate("Saved file: {}\n\n").str(), filePath_.u8string());
                }

                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

        options_description loadOptions(translate("Load Options"));
        loadOptions.add_options()
            ("help,h", translate("Print this help messages for load command.").str().c_str())
            ("path,p", value<std::filesystem::path>(), translate("File path to be loaded").str().c_str());

        AddCommand({
            "load", "l", translate("load todo list from the file"), loadOptions,
            [this](const variables_map& variables, const options_description& description)
            ->pair<int, ConsoleCli::NextAction>
            {
                if (variables.count("help"))
                {
                    cout << description << "\n";
                }
                else
                {
                    std::filesystem::path path;
                    if (variables.count("path"))
                    {
                        filePath_ = variables["path"].as<std::filesystem::path>();
                    }
                    taskList_.Load(filePath_);
                    SetStatus(filePath_.u8string());
                    cout << format(translate("Loaded file: {}\n\n").str(), filePath_.u8string());
                }

                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

        AddCommand({
            "clear", "c", translate("clear todo list"), loadOptions,
            [this](const variables_map& variables, const options_description& description)
            ->pair<int, ConsoleCli::NextAction>
            {
                if (variables.count("help"))
                {
                    cout << description << "\n";
                }
                else
                {
                    taskList_.Clear();
                    SetStatus(filePath_.u8string() + "*");
                    cout << format(translate("Cleared todo list\n\n").str());
                }

                return make_pair(0, NextAction::WAIT_INPUT);
            }
        });

    }
}
