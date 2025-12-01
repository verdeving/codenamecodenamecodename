#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_compilation_unit
#define iris_guard_cornea_compilation_unit
#include "Type.hpp"
#include "Mode.hpp"
#include "System.hpp"
#include "Architecture.hpp"
#include "../Core/Position.hpp"

namespace Iris::Cornea
{
    struct [[nodiscard]] CompilationUnit final
    {
        Position start, end;

        std::string_view id, name;

        System system = System::
        #ifdef iris_linux
        Linux
        #elifdef iris_darwin
        Darwin
        #elifdef iris_windows
        Windows
        #endif
        ;

        Architecture architecture = Architecture::
        #ifdef iris_darwin
        Arm64
        #else
        Amd64
        #endif
        ;

        Type type = Type::App;

        Mode mode = Mode::Debug;

        [[nodiscard]] auto operator==(const CompilationUnit& rhs) const noexcept -> bool;
    };
}

#endif
#endif