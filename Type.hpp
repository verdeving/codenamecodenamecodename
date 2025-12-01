#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_type
#define iris_guard_cornea_type
#include <string>

namespace Iris::Cornea
{
    enum class [[nodiscard]] Type : std::uint8_t
    {
        App,
        Lib
    };

    [[nodiscard]] auto stringify(const Type type) noexcept -> std::string;
}

#endif
#endif