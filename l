#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Iris.hpp"
#include "Irken.hpp"
#include "../Core/Sets.hpp"
#include "../Core/Error.hpp"

namespace Iris
{
    [[nodiscard]] auto iris(const std::string& file, const std::string content, const Cornea::
    CompilationUnit& unit, Main& main) noexcept -> bool
    {
        Lexer<Irken> lexer;
        {
            Position start, actual{1uz, 0uz};
            const char* offset;
            std::size_t length = 0uz;
            enum class [[nodiscard]] Context : std::uint8_t
            {
                General,
                PreComment,
                SingleLineComment,
                MultiLineComment,
                MultiLineEndComment
            };
            using enum Context;
            Context context = General;
            for(const char& character : content)
            {
                if(character not_eq '\n')
                    if(actual.column++ == std::numeric_limits<std::uint32_t>::max())
                    {
                        Error::log<3uz>(Language::iris, file, unit, "the number of columns " +
                        Error::numeric + std::to_string(actual.column) + Error::normal +
                        " at the line " + Error::numeric + std::to_string(actual.line) + Error
                        ::normal + " reached or exceeded the maximum number of columns " +
                        Error::numeric + '2' + Error::token + '^' + Error::numeric + "32" +
                        Error::normal);
                        return false;
                    }
                switch(context)
                {
                    case General:
                        switch(character)
                        {
                            using enum Irken;
                            case '_':
                            case $alphanumeric:
                                if(length++ == 0uz)
                                {
                                    offset = &character;
                                    start = actual;
                                }
                            break;
                            case $whitespace:
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                            break;
                            case '{':
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                                tokenize(sm_start_node, actual, lexer);
                            break;
                            case '}':
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                                tokenize(sm_end_node, actual, lexer);
                            break;
                            case '`':
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                                context = PreComment;
                                start = actual;
                            break;
                            default:
                                Error::log<2uz>(Language::iris, file, actual, unit,
                                "the character " + Error::data + map(character) + Error::normal
                                + " is unrecognized");
                                return false;
                        }
                    break;
                    case PreComment:
                        switch(character)
                        {
                            case '`':
                                context = SingleLineComment;
                            break;
                            case '*':
                                context = MultiLineComment;
                            break;
                            default:
                                Error::log<1uz>(Language::iris, file, actual, unit,
                                "the character " + Error::data + map(character) + Error::normal
                                + " is unrecognized as a pre-comment character, valid "
                                "pre-comment characters are " + Error::data + '`' + Error::
                                normal + " for single-line comments, or " + Error::data + '*' +
                                Error::normal + " for multi-line comments");
                                return false;
                        }
                    break;
                    case SingleLineComment:
                        if(character == '\n')
                            context = General;
                    break;
                    case MultiLineComment:
                        if(character == '*')
                            context = MultiLineEndComment;
                    break;
                    case MultiLineEndComment:
                        switch(character)
                        {
                            case '`':
                                context = General;
                            break;
                            case '*':
                            break;
                            default:
                                context = MultiLineComment;
                        }
                }
                if(character == '\n')
                {
                    if(actual.line++ == std::numeric_limits<std::uint32_t>::max())
                    {
                        Error::log<4uz>(Language::iris, file, unit, "the number of lines " +
                        Error::numeric + std::to_string(actual.line) + Error::normal +
                        " reached or exceeded the maximum number of lines " + Error::numeric +
                        '2' + Error::token + '^' + Error::numeric + "32" + Error::normal);
                        return false;
                    }
                    actual.column = 0ul;
                }
            }
            switch(context)
            {
                case General:
                    tokenize(length, start, actual, std::string_view(offset, length), lexer);
                break;
                case SingleLineComment:
                break;
                case PreComment:
                    Error::log<5uz>(Language::cornea, file, unit, "expected " + Error::token +
                    '`' + Error::normal + " for a single-line comment or " + Error::token + '*'
                    + Error::normal + " for a multi-line comment, after the pre-comment " +
                    Error::token + '`' + Error::normal + " before the end of the file at " +
                    start.stringify());
                    return false;
                case MultiLineComment:
                case MultiLineEndComment:
                    Error::log<6uz>(Language::iris, file, unit, "expected " + Error::token + (
                    context == MultiLineComment ? "*`" : "`") + Error::normal +
                    " to end a multi-line comment starting at " + start.stringify() +
                    ", before the end of the file");
                    return false;
            }
        }
        lexer.compact();
        debug(file, lexer);
        AST ast;
        std::size_t nodes = 0uz;
        enum class [[nodiscard]] Context : std::uint8_t
        {
            Module,
            Main,
            Block,
        };
        using enum Context;
        Context context = Module;
        bool is_main = false;
        for(const Token<Irken>& token : lexer.tokens)
            switch(context)
            {
                using enum Irken;
                case Module:
                    switch(token.kind)
                    {
                        case kw_main:
                            if(unit.type not_eq Cornea::Type::App)
                            {
                                Error::log<8uz>(Language::iris, file, ending(lexer, token),
                                unit, "the type of the compilation unit is not " + Error::token
                                + "app" + Error::normal + ", you can't use " + Error::token +
                                "main" + Error::normal);
                                return false;
                            }
                            else if(main.loaded)
                            {
                                Error::log<9uz>(Language::iris, file, ending(lexer, token),
                                unit, "there is already another " + Error::token + "main" +
                                Error::normal + " at " + Error::italic + Error::path + main.
                                file + Error::normal + Error::token + " @ " + main.start.
                                rangify(main.end));
                                return false;
                            }
                            context = Main;
                            main.loaded = true;
                            main.file = file;
                        break;
                        default:
                            Error::log<7uz>(Language::iris, file, ending(lexer, token), unit,
                            "expected " + Error::token + (unit.type == Cornea::Type::App ?
                            "main" + Error::normal + " to declare the main method, " : "") +
                            ", found " + symbol(lexer, token) + Error::normal + " starting at "
                            + token.start.stringify());
                            return false;
                    }
                break;
                case Main:
                    if(token.kind not_eq sm_start_node)
                    {
                        Error::log<10uz>(Language::iris, file, ending(lexer, token), unit,
                        "expected " + Error::token + '{' + Error::normal +
                        " to start the body of " + Error::token + "main" + Error::normal);
                        return false;
                    }
                    is_main = true;
                    context = Block;
                    main.start = token.start;
                    ast.emplace_back(StartMain{});
                break;
                case Block:
                    switch(token.kind)
                    {
                        case sm_end_node:
                            if(nodes == 0uz)
                            {
                                context = Module;
                                if(is_main)
                                {
                                    is_main = false;
                                    main.end = token.start;
                                    ast.emplace_back(EndMain{});
                                }
                            }
                        break;
                        default:
                    }
                break;
            }
        translate(file, ast);
        return true;
    }
}

#endif
