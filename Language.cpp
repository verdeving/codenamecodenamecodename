#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Language.hpp"

namespace Iris
{
    [[nodiscard]] auto stringify(const Language language) noexcept -> std::string
    {
        using enum Language;
        switch(language)
        {
            case cornea:
                return "cornea";
            case iris:
                return "iris";
        }
    }
}

#endif