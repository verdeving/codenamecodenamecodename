#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_language
#define iris_guard_core_language
#include <string>

namespace Iris
{
    enum class [[nodiscard]] Language : std::uint8_t
    {
        cornea,
        iris
    };

    [[nodiscard]] auto stringify(const Language language) noexcept -> std::string;
}

#endif
#endif