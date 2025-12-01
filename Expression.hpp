#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_expression
#define iris_guard_iris_expression
#include <variant>

namespace Iris
{
    using Expression = std::variant<>;
}

#endif
#endif