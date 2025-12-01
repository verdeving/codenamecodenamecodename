#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_main
#define iris_guard_iris_main
#include "../Core/Position.hpp"

namespace Iris
{
    struct [[nodiscard]] Main final
    {
        bool loaded = false;
        
        Position start, end;

        std::string_view file;
    };

    struct [[nodiscard]] StartMain final{};

    struct [[nodiscard]] EndMain final{};
}

#endif
#endif