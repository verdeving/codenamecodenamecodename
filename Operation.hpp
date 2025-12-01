#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_lens_operation
#define iris_guard_lens_operation
#include <variant>
#include "Entry.hpp"

namespace Iris::Lens
{
    using Operation = std::variant<Entry, Exit>;
}

#endif
#endif