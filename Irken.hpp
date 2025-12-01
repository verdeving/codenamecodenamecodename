#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_iris_irken
#define iris_guard_iris_irken
#include "AST.hpp"
#include "../Core/Token.hpp"

namespace Iris
{
    enum class [[nodiscard]] Irken : std::uint8_t
    {
        unknown,
        sm_start_node, // {
        sm_end_node, // }
        kw_main // main
    };

    [[nodiscard]] auto symbol(const Lexer<Irken>& lexer, const Token<Irken>& token, const bool
    debug = false) noexcept -> std::string;

    [[nodiscard]] auto ending(const Lexer<Irken>& lexer, const Token<Irken>& token) noexcept ->
    Position;

    auto tokenize(const Irken kind, const Position position, Lexer<Irken>& lexer) noexcept -> void;

    auto tokenize(std::size_t& length, const Position start, const Position position, const std::
    string_view content, Lexer<Irken>& lexer) noexcept -> void;

    auto debug(const std::string& file, const Lexer<Irken>& lexer) noexcept -> void;

    auto translate(const std::string& file, const AST& ast) noexcept -> void;
}

#endif
#endif