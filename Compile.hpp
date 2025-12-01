#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_compile
#define iris_guard_core_compile
#include <string>

namespace Iris
{
    auto compile(std::string name) noexcept -> void;
}

#endif
#endif