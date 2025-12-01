#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "System.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto stringify(const System system) noexcept -> std::string
    {
        switch(system)
        {
            using enum System;
            case Linux:
                return "linux";
            case Darwin:
                return "darwin";
            case Windows:
                return "windows";
        }
    }
}

#endif