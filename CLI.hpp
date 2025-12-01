#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_cli
#define iris_guard_core_cli

namespace Iris::CLI
{
    auto process(int argc, char** argv) noexcept -> void;
}

#endif
#endif