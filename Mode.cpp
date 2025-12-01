#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Mode.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto stringify(const Mode mode) noexcept -> std::string
    {
        switch(mode)
        {
            using enum Mode;
            case Debug:
                return "debug";
            case Release:
                return "release";
        }
    }
}

#endif