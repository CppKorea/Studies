#include <iostream>
#include <fmt/format.h>
#include "ConsoleTodoList.h"
#include "TaskList.h"


int main(int argc, char* argv[])
{
    using fmt::format;

    try
    {
        practicalCpp::TaskList taskList;
        practicalCpp::ConsoleTodoList console{ taskList };

        return console.Execute(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << format("ERROR: {}\n", e.what());
        return -1;
    }
    catch (...)
    {
        std::cerr << "ERROR: Unhandled seh exception\n";
        return -2;
    }
}
