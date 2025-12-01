#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_cornea_corken
#define iris_guard_cornea_corken
#include "../Core/Token.hpp"
#include "CompilationUnit.hpp"

namespace Iris::Cornea
{
    enum class [[nodiscard]] Corken : std::uint8_t
    {
        unknown,
        identifier,
        numeric,
        sm_end_sequence, // ;
        sm_start_node, // {
        sm_end_node, // }
        sm_equal, // =
        kw_name, // name
        kw_system, // system
        kw_architecture, // architecture
        kw_type, // type
        kw_mode, // mode
        // for system
        kw_linux, // linux
        kw_darwin, // darwin
        kw_windows, // windows
        // for architecture
        kw_amd64, // amd64
        kw_arm64, // arm64
        kw_riscv64, // riscv64
        // for type
        kw_app, // app
        kw_lib, // lib
        // for mode
        kw_debug, // debug
        kw_release // release
    };

    [[nodiscard]] auto symbol(const Lexer<Corken>& lexer, const Token<Corken>& token, const bool
    debug = false) noexcept -> std::string;

    [[nodiscard]] auto ending(const Lexer<Corken>& lexer, const Token<Corken>& token) noexcept ->
    Position;

    [[nodiscard]] auto tokenize(const std::string_view content) noexcept -> Corken;

    auto tokenize(const Corken kind, const Position position, Lexer<Corken>& lexer) noexcept ->
    void;

    auto tokenize(std::size_t& length, const Position start, const Position position, const std::
    string_view content, Lexer<Corken>& lexer) noexcept -> void;

    auto debug(const std::string& file, const Lexer<Corken>& lexer) noexcept -> void;

    auto debug(const std::string& file, const std::vector<CompilationUnit>& units) noexcept -> void
    ;
}

#endif
#endif