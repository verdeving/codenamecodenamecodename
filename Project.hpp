#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_project
#define iris_guard_core_project
#include <string>
#include <vector>

namespace Iris
{
    struct [[nodiscard]] Project final
    {
        std::string name, base, src, out, cornea;

        std::vector<std::string> iris;

        Project(std::string&& name) noexcept;
    };
}

#endif
#endif