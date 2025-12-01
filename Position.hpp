#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_position
#define iris_guard_core_position
#include <string>

namespace Iris
{
    struct [[nodiscard]] Position final
    {
        std::uint32_t line, column;

        [[nodiscard]] auto stringify(const bool coloured = true) const noexcept -> std::string;

        [[nodiscard]] auto rangify(const Position end, const bool coloured = true) const noexcept
        -> std::string;
    };
}

#endif
#endif