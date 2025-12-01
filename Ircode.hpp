#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_ircode
#define iris_guard_iris_ircode
#include <string>

namespace Iris::Ircode
{
    inline constexpr std::string start_main = "000", end_main = "001";
}

#endif
#endif