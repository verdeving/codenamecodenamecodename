#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_node
#define iris_guard_iris_node
#include "Main.hpp"
#include "Expression.hpp"

namespace Iris
{
    using Node = std::variant<StartMain, EndMain>;
}

#endif
#endif