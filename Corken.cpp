#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Corken.hpp"
#include "../Core/Sets.hpp"
#include "../Core/File.hpp"
#include "../Core/Error.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto symbol(const Lexer<Corken>& lexer, const Token<Corken>& token, const bool
    debug) noexcept -> std::string
    {
        using enum Corken;
        if(debug)
            switch(token.kind)
            {
                case unknown:
                    return "unknown: " + std::string(token.symbol(lexer).content);
                case identifier:
                    return "identifier: " + std::string(token.symbol(lexer).content);
                case numeric:
                    return "numeric: " + std::string(token.symbol(lexer).content);
                case sm_end_sequence:
                    return std::string(1uz, ';');
                case sm_start_node:
                    return std::string(1uz, '{');
                case sm_end_node:
                    return std::string(1uz, '}');
                case sm_equal:
                    return std::string(1uz, '=');
                case kw_name:
                    return "name";
                case kw_system:
                    return "system";
                case kw_architecture:
                    return "architecture";
                case kw_type:
                    return "type";
                case kw_mode:
                    return "mode";
                case kw_linux:
                    return "linux";
                case kw_darwin:
                    return "darwin";
                case kw_windows:
                    return "windows";
                case kw_amd64:
                    return "amd64";
                case kw_arm64:
                    return "arm64";
                case kw_riscv64:
                    return "riscv64";
                case kw_app:
                    return "app";
                case kw_lib:
                    return "lib";
                case kw_debug:
                    return "debug";
                case kw_release:
                    return "release";
            }
        else
            switch(token.kind)
            {
                case unknown:
                case identifier:
                case numeric:
                    return Error::data + token.symbol(lexer).content;
                case sm_end_sequence:
                    return Error::token + ';';
                case sm_start_node:
                    return Error::token + '{';
                case sm_end_node:
                    return Error::token + '}';
                case sm_equal:
                    return Error::token + '=';
                case kw_name:
                    return Error::token + "name";
                case kw_system:
                    return Error::token + "system";
                case kw_architecture:
                    return Error::token + "architecture";
                case kw_type:
                    return Error::token + "type";
                case kw_mode:
                    return Error::token + "mode";
                case kw_linux:
                    return Error::token + "linux";
                case kw_darwin:
                    return Error::token + "darwin";
                case kw_windows:
                    return Error::token + "windows";
                case kw_amd64:
                    return Error::token + "amd64";
                case kw_arm64:
                    return Error::token + "arm64";
                case kw_riscv64:
                    return Error::token + "riscv64";
                case kw_app:
                    return Error::token + "app";
                case kw_lib:
                    return Error::token + "lib";
                case kw_debug:
                    return Error::token + "debug";
                case kw_release:
                    return Error::token + "release";
            }
    }

    [[nodiscard]] auto ending(const Lexer<Corken>& lexer, const Token<Corken>& token) noexcept ->
    Position
    {
        switch(token.kind)
        {
            using enum Corken;
            default:
                return token.symbol(lexer).end;
            case sm_end_sequence:
            case sm_start_node:
            case sm_end_node:
            case sm_equal:
                return token.start;
            case kw_system:
            case kw_darwin:
                return Position{token.start.line, token.start.column + 6u};
            case kw_architecture:
                return Position{token.start.line, token.start.column + 12u};
            case kw_name:
            case kw_type:
            case kw_mode:
                return Position{token.start.line, token.start.column + 4u};
            case kw_linux:
            case kw_amd64:
            case kw_arm64:
            case kw_debug:
                return Position{token.start.line, token.start.column + 5u};
            case kw_windows:
            case kw_riscv64:
            case kw_release:
                return Position{token.start.line, token.start.column + 7u};
            case kw_app:
            case kw_lib:
                return Position{token.start.line, token.start.column + 3u};
        }
    }

    [[nodiscard]] auto tokenize(const std::string_view content) noexcept -> Corken
    {
        using enum Corken;
        Corken mode = numeric;
        switch(content[0])
        {
            case '_':
                return unknown;
            case '0':
                return content.size() == 1uz ? numeric : unknown;
            case $digit_non_zero:
            break;
            default:
                mode = identifier;
        }
        for(std::size_t x = 1uz; x < content.size(); ++x)
            switch(mode)
            {
                case numeric:
                    switch(content[x])
                    {
                        default:
                            return unknown;
                        case $digit:
                    }
                break;
                case identifier:
                    switch(content[x])
                    {
                        default:
                            return unknown;
                        case '_':
                        case $alphanumeric:
                    }
                break;
                default:
            }
        return mode;
    }

    auto tokenize(const Corken kind, const Position position, Lexer<Corken>& lexer) noexcept ->
    void
    {
        lexer.tokens.emplace_back(kind, position);
    }

    auto tokenize(std::size_t& length, const Position start, const Position position, const std::
    string_view content, Lexer<Corken>& lexer) noexcept -> void
    {
        if(length > 0uz)
        {
            length = 0uz;
            using enum Corken;
            const Corken kind = content == "name" ? kw_name : content == "system" ? kw_system :
            content == "architecture" ? kw_architecture : content == "type" ? kw_type : content ==
            "mode" ? kw_mode : content == "linux" ? kw_linux : content == "darwin" ? kw_darwin :
            content == "windows" ? kw_windows : content == "amd64" ? kw_amd64 : content == "arm64"
            ? kw_arm64 : content == "riscv64" ? kw_riscv64 : content == "app" ? kw_app : content ==
            "lib" ? kw_lib : content == "debug" ? kw_debug : content == "release" ? kw_release :
            tokenize(content);
            if(kind == unknown or kind == numeric or kind == identifier)
            {
                lexer.tokens.emplace_back(kind, start, lexer.symbols.size());
                lexer.symbols.emplace_back(position, content);
            }
            else
                lexer.tokens.emplace_back(kind, start);
        }
    }

    auto debug(const std::string& file, const Lexer<Corken>& lexer) noexcept -> void
    {
        std::string spaces, content = "printing the token tree for ";
        content += file;
        content += "...\n";
        for(const Token<Corken>& token : lexer.tokens)
        {
            content.append(1uz, '\n');
            using enum Corken;
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

    auto debug(const std::string& file, const std::vector<CompilationUnit>& units) noexcept -> void
    {
        std::string content = "printing the units tree for ";
        content += file;
        content += "...\n";
        for(const CompilationUnit& unit : units)
        {
            content.append(1uz, '\n');
            content += "unit ";
            content += unit.id;
            content.append(1uz, ' ');
            content += unit.start.rangify(unit.end, false);
            content += "\n{\n    let name be ";
            content += unit.name;
            content += "\n    let system be ";
            content += stringify(unit.system);
            content += "\n    let architecture be ";
            content += stringify(unit.architecture);
            content += "\n    let type be ";
            content += stringify(unit.type);
            content += "\n    let mode be ";
            content += stringify(unit.mode);
            content += "\n}\n";
        }
        content.pop_back();
        File::write_text(File::units_tree(file), content);
    }
}

#endif