#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_token
#define iris_guard_core_token
#include "Position.hpp"
#include <vector>
#include <type_traits>

namespace Iris
{
    struct [[nodiscard]] Symbol final
    {
        Position end;

        std::string_view content;
    };

    template<class T> requires std::is_scoped_enum_v<T> struct [[nodiscard]] Token;

    template<class T> struct [[nodiscard]] Lexer final
    {
        std::vector<Symbol> symbols;

        std::vector<Token<T>> tokens;

        auto compact() noexcept -> void
        {
            symbols.shrink_to_fit();
            tokens.shrink_to_fit();
        }
    };

    template<class T> requires std::is_scoped_enum_v<T> struct [[nodiscard]] Token final
    {
        T kind;

        Position start;

        const std::size_t index;

        [[nodiscard]] auto symbol(Lexer<T>& lexer) noexcept -> Symbol&
        {
            return lexer.symbols[index];
        }

        [[nodiscard]] auto symbol(const Lexer<T>& lexer) const noexcept -> const Symbol&
        {
            return lexer.symbols[index];
        }
    };
}

#endif
#endif