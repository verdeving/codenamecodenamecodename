#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_iris
#define iris_guard_iris_iris
#include "Main.hpp"
#include "../Cornea/CompilationUnit.hpp"

namespace Iris
{
    [[nodiscard]] auto iris(const std::string& file, const std::string content, const Cornea::
    CompilationUnit& unit, Main& main) noexcept -> bool;
}

#endif
#endif