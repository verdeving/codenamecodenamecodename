#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Project.hpp"
#include <filesystem>

namespace Iris
{
    Project::Project(std::string&& pname) noexcept : name(std::forward<std::string>(pname)), base(
    name + ".irisproject"
    #ifdef iris_windows
    "\\"
    #else
    "/"
    #endif
    ), src(base + "src"), out(base + "out"), cornea(base + name + ".cornea")
    {
        for(const std::filesystem::directory_entry& entry : std::filesystem::
        recursive_directory_iterator(src, std::filesystem::directory_options::
        follow_directory_symlink))
            if (entry.is_regular_file() and std::filesystem::canonical(entry.path()).extension() ==
            ".iris")
                iris.emplace_back(entry.path().string());
    }
}

#endif