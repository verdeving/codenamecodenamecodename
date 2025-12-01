#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "CompilationUnit.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto CompilationUnit::operator==(const CompilationUnit& rhs) const noexcept ->
    bool
    {
        return name == rhs.name and system == rhs.system and architecture == rhs.architecture and
        type == rhs.type and mode == rhs.mode;
    }
}

#endif