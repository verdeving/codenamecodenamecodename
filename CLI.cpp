#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "CLI.hpp"
#include "Create.hpp"
#include "Compile.hpp"

namespace Iris::CLI
{
    auto process(int argc, char** argv) noexcept -> void
    {
        switch(argc)
        {
            case 3:
                const std::string_view command(argv[1]);
                if(command == "create")
                    create(argv[2]);
                else if(command == "compile")
                    compile(argv[2]);
            break;
        }
    }
}

#endif