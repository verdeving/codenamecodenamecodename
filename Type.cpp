#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Type.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto stringify(const Type type) noexcept -> std::string
    {
        switch(type)
        {
            using enum Type;
            case App:
                return "app";
            case Lib:
                return "lib";
        }
    }
}

#endif