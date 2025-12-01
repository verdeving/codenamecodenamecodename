#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_ast
#define iris_guard_iris_ast
#include "Node.hpp"
#include <vector>

namespace Iris
{
    using AST = std::vector<Node>;
}

#endif
#endif