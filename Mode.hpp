#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_mode
#define iris_guard_cornea_mode
#include <string>

namespace Iris::Cornea
{
    enum class [[nodiscard]] Mode : std::uint8_t
    {
        Debug,
        Release
    };

    [[nodiscard]] auto stringify(const Mode mode) noexcept -> std::string;
}

#endif
#endif