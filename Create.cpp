#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Create.hpp"
#include <fstream>
#include <filesystem>

namespace Iris
{
    auto create(const std::string name) noexcept -> void
    {
        const std::string project = name + ".irisproject/";
        std::filesystem::create_directory(project);
        std::filesystem::create_directory(project + "out");
        std::filesystem::create_directory(project + "src");
        const std::string content = name + "\n{\n}";
        std::ofstream(project + name + ".cornea").write(content.c_str(), content.size());
    }
}

#endif