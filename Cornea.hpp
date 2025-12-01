#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_cornea
#define iris_guard_cornea_cornea
#include "CompilationUnit.hpp"
#include <vector>
#include <optional>

namespace Iris::Cornea
{
    [[nodiscard]] auto cornea(const std::string& file, const std::string content) noexcept -> std::
    optional<std::vector<CompilationUnit>>;
}

#endif
#endif