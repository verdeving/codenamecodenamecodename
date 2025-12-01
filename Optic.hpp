#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_optic_optic
#define iris_guard_optic_optic
#include "../Lens/IR.hpp"
#include "../Cornea/CompilationUnit.hpp"

namespace Iris::Optic
{
    auto optic(const std::string file, const Cornea::CompilationUnit& unit, Lens::IR& ir) noexcept
    -> void;
}

#endif
#endif