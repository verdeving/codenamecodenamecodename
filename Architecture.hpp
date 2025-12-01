#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_architecture
#define iris_guard_cornea_architecture
#include <string>

namespace Iris::Cornea
{
    enum class [[nodiscard]] Architecture : std::uint8_t
    {
        Amd64,
        Arm64,
        Riscv64
    };

    [[nodiscard]] auto stringify(const Architecture architecture) noexcept -> std::string;
}

#endif
#endif