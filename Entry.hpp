#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_lens_entry
#define iris_guard_lens_entry

namespace Iris::Lens
{
    struct [[nodiscard]] Entry final{};

    struct [[nodiscard]] Exit final{};
}

#endif
#endif