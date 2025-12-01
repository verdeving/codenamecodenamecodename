#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_create
#define iris_guard_core_create
#include <string>

namespace Iris
{
    auto create(const std::string name) noexcept -> void;
}

#endif
#endif