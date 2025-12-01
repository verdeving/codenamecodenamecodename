#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Irken.hpp"
#include "Ircode.hpp"
#include "../Core/File.hpp"
#include "../Core/Error.hpp"

namespace Iris
{
    [[nodiscard]] auto symbol(const Lexer<Irken>& lexer, const Token<Irken>& token, const bool
    debug) noexcept -> std::string
    {
        using enum Irken;
        if(debug)
            switch(token.kind)
            {
                case unknown:
                    return "unknown: " + std::string(token.symbol(lexer).content);
                case sm_start_node:
                    return std::string(1uz, '{');
                case sm_end_node:
                    return std::string(1uz, '}');
                case kw_main:
                    return "main";
            }
        else
            switch(token.kind)
            {
                case unknown:
                    return Error::data + token.symbol(lexer).content;
                case sm_start_node:
                    return Error::token + '{';
                case sm_end_node:
                    return Error::token + '}';
                case kw_main:
                    return Error::token + "main";
            }
    }

    [[nodiscard]] auto ending(const Lexer<Irken>& lexer, const Token<Irken>& token) noexcept ->
    Position
    {
        switch(token.kind)
        {
            using enum Irken;
            default:
                return token.symbol(lexer).end;
            case sm_start_node:
            case sm_end_node:
                return token.start;
            case kw_main:
                return Position{token.start.line, token.start.column + 4u};
        }
    }

    auto tokenize(const Irken kind, const Position position, Lexer<Irken>& lexer) noexcept -> void
    {
        lexer.tokens.emplace_back(kind, position);
    }

    auto tokenize(std::size_t& length, const Position start, const Position position, const std::
    string_view content, Lexer<Irken>& lexer) noexcept -> void
    {
        if(length > 0uz)
        {
            length = 0uz;
            using enum Irken;
            const Irken kind = content == "main" ? kw_main : unknown;
            if(kind == unknown)
            {
                lexer.tokens.emplace_back(kind, start, lexer.symbols.size());
                lexer.symbols.emplace_back(position, content);
            }
            else
                lexer.tokens.emplace_back(kind, start);
        }
    }

    auto debug(const std::string& file, const Lexer<Irken>& lexer) noexcept -> void
    {
        std::string spaces, content = "printing the token tree for ";
        content += file;
        content += "...\n";
        for(const Token<Irken>& token : lexer.tokens)
        {
            content.append(1uz, '\n');
            using enum Irken;
            if(token.kind == sm_end_node and not spaces.empty())
            {
                spaces.pop_back();
                spaces.pop_back();
                spaces.pop_back();
                spaces.pop_back();
            }
            content += spaces;
            if(token.kind == sm_start_node)
                spaces += "    ";
            content += "starting at ";
            content += token.start.stringify(false);
            content += " and ending at ";
            content += ending(lexer, token).stringify(false);
            content += ", token ";
            content += symbol(lexer, token, true);
        }
        File::write_text(File::token_tree(file), content);
    }

    auto translate(const std::string& file, const AST& ast) noexcept -> void
    {
        std::string content;
        for(const Node& node : ast)
            std::visit([&](auto&& mnode)
            {
                using T = std::decay_t<decltype(mnode)>;
                if constexpr(std::same_as<T, StartMain>)
                    content += Ircode::start_main;
                else if constexpr(std::same_as<T, EndMain>)
                    content += Ircode::end_main;
            }, node);
        File::write(File::iris_abstract_tree(file), content);
    }
}

#endif