#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_system
#define iris_guard_cornea_system
#include <string>

namespace Iris::Cornea
{
    enum class [[nodiscard]] System : std::uint8_t
    {
        Linux,
        Darwin,
        Windows
    };

    [[nodiscard]] auto stringify(const System system) noexcept -> std::string;
}

#endif
#endif