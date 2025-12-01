#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_lens_lens
#define iris_guard_lens_lens
#include <optional>
#include "IR.hpp"
#include "../Cornea/CompilationUnit.hpp"

namespace Iris::Lens
{
    [[nodiscard]] auto lens(const std::string& file, const Cornea::CompilationUnit& unit, const
    std::string content) noexcept -> std::optional<IR>;
}

#endif
#endif