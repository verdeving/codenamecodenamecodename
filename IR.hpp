#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_lens_ir
#define iris_guard_lens_ir
#include <vector>
#include "Operation.hpp"

namespace Iris::Lens
{
    using IR = std::vector<Operation>;
}

#endif
#endif