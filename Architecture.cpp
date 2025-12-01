#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Architecture.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto stringify(const Architecture architecture) noexcept -> std::string
    {
        switch(architecture)
        {
            using enum Architecture;
            case Amd64:
                return "amd64";
            case Arm64:
                return "arm64";
            case Riscv64:
                return "riscv64";
        }
    }
}

#endif