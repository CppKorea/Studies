#include "TaskList.h"
#include <fstream>
#include <boost/locale.hpp>
#include <fmt/format.h>
#include <json/json.h>

namespace practicalCpp
{
    using std::filesystem::path;
    using std::function;
    using std::locale;
    using std::lock_guard;
    using std::logic_error;
    using std::shared_lock;
    using std::shared_mutex;
    using std::string;
    using boost::locale::translate;
    using fmt::format;


    TaskList::TaskList()
    {
    }

    TaskList::~TaskList()
    {
    }

    int64_t TaskList::AddTask(const string& title, const Task::State& state)
    {
        lock_guard<shared_mutex> lock{ mutex_ };
        tasks_[++lastId_] = Task{ title, state };
        return lastId_;
    }

    void TaskList::RemoveTask(const int64_t id)
    {
        lock_guard<shared_mutex> lock{ mutex_ };
        if (const auto& it = tasks_.find(id); it != tasks_.cend())
        {
            tasks_.erase(it);
        }
        else
        {
            throw logic_error(format(translate("ID #{} is not found from todo list.").str(), id));
        }
    }

    Task TaskList::GetTask(const int64_t id)
    {
        shared_lock<shared_mutex> lock{ mutex_ };
        if (const auto& it = tasks_.find(id); it != tasks_.cend())
        {
            return it->second;
        }
        else
        {
            throw logic_error(format(translate("ID #{} is not found from todo list.").str(), id));
        }
    }

    void TaskList::UpdateTask(const int64_t id, const Task& task)
    {
        lock_guard<shared_mutex> lock{ mutex_ };
        if (const auto& it = tasks_.find(id); it != tasks_.cend())
        {
            it->second = task;
        }
        else
        {
            throw logic_error(format(translate("ID #{} is not found from todo list.").str(), id));
        }
    }

    void TaskList::Enumerate(const function<void(const int64_t, const Task&)>& visit)
    {
        shared_lock<shared_mutex> lock{ mutex_ };
        for (const auto& task : tasks_)
        {
            visit(task.first, task.second);
        }
    }

    void TaskList::Clear()
    {
        lock_guard<shared_mutex> lock{ mutex_ };
        lastId_ = 0;
        tasks_.clear();
    }

    void TaskList::Save(const path& path)
    {
        Json::Value root;
        root["tasks"] = Json::Value(Json::arrayValue);

        Json::Value taskJson;
        {
            shared_lock<shared_mutex> lock{ mutex_ };
            root["last-id"] = lastId_;
            for (const auto& task : tasks_)
            {
                taskJson["id"] = task.first;
                taskJson["title"] = task.second.GetTitle();
                taskJson["state"] = Task::ToString(task.second.GetState());
                root["tasks"].append(taskJson);
            }
        }

        std::ofstream file(path, std::ofstream::binary);
        file.imbue(locale());

        Json::StreamWriterBuilder builder;
        builder["indentation"] = "  ";
        builder["emitUTF8"] = true;

        const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        writer->write(root, &file);
    }

    void TaskList::Load(const path& path)
    {
        Json::CharReaderBuilder builder;
        Json::String errors;

        std::ifstream file(path, std::ifstream::binary);
        file.imbue(locale());

        if (Json::Value root; Json::parseFromStream(builder, file, &root, &errors))
        {
            lock_guard<shared_mutex> lock{ mutex_ };
            lastId_ = root["last-id"].asInt64();
            tasks_.clear();
            for (const auto& taskJson : root["tasks"])
            {
                tasks_[taskJson["id"].asInt64()] = Task
                {
                    taskJson["title"].asString(),
                    Task::ToState(taskJson["state"].asString())
                };
            }
        }
    }
}
