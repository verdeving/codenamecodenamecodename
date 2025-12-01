#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Cornea.hpp"
#include "Corken.hpp"
#include "../Core/Sets.hpp"
#include "../Core/Error.hpp"

namespace Iris::Cornea
{
    [[nodiscard]] auto cornea(const std::string& file, const std::string content) noexcept -> std
    ::optional<std::vector<CompilationUnit>>
    {
        Lexer<Corken> lexer;
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
                        Error::log<3uz>(Language::cornea, file, "the number of columns " + Error::
                        numeric + std::to_string(actual.column) + Error::normal + " at the line " +
                        Error::numeric + std::to_string(actual.line) + Error::normal +
                        " reached or exceeded the maximum number of columns " + Error::numeric +
                        '2' + Error::token + '^' + Error::numeric + "32" + Error::normal);
                        return std::nullopt;
                    }
                switch(context)
                {
                    case General:
                        switch(character)
                        {
                            using enum Corken;
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
                            case '=':
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                                tokenize(sm_equal, actual, lexer);
                            break;
                            case ';':
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                                tokenize(sm_end_sequence, actual, lexer);
                            break;
                            case '`':
                                tokenize(length, start, actual, std::string_view(offset, length),
                                lexer);
                                context = PreComment;
                                start = actual;
                            break;
                            default:
                                Error::log<2uz>(Language::cornea, file, actual, "the character " +
                                Error::data + map(character) + Error::normal + " is unrecognized");
                                return std::nullopt;
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
                                Error::log<1uz>(Language::cornea, file, actual, "the character " +
                                Error::data + map(character) + Error::normal +
                                " is unrecognized as a pre-comment character, valid pre-comment "
                                "characters are " + Error::data + '`' + Error::normal +
                                " for single-line comments, or " + Error::data + '*' + Error::
                                normal + " for multi-line comments");
                                return std::nullopt;
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
                        Error::log<4uz>(Language::cornea, file, "the number of lines " + Error::
                        numeric + std::to_string(actual.line) + Error::normal +
                        " reached or exceeded the maximum number of lines " + Error::numeric + '2'
                        + Error::token + '^' + Error::numeric + "32" + Error::normal);
                        return std::nullopt;
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
                    Error::log<5uz>(Language::cornea, file, "expected " + Error::token + '`' +
                    Error::normal + " for a single-line comment or " + Error::token + '*' + Error::
                    normal + " for a multi-line comment, after the pre-comment " + Error::token +
                    '`' + Error::normal + " before the end of the file at " + start.stringify());
                    return std::nullopt;
                case MultiLineComment:
                case MultiLineEndComment:
                    Error::log<6uz>(Language::cornea, file, "expected " + Error::token + (context
                    == MultiLineComment ? "*`" : "`") + Error::normal +
                    " to end a multi-line comment starting at " + start.stringify() +
                    ", before the end of the file");
                    return std::nullopt;
            }
        }
        lexer.compact();
        debug(file, lexer);
        std::vector<CompilationUnit> units;
        CompilationUnit unit;
        enum class [[nodiscard]] Context : std::uint8_t
        {
            General,
            StartNode,
            Unit,
            Name,
            System,
            Architecture,
            Type,
            Mode
        };
        using enum Context;
        Context context = General;
        enum class [[nodiscard]] Assignment : std::uint8_t
        {
            Equal,
            Value,
            Sentence
        };
        using enum Assignment;
        Assignment subcontext = Equal;
        for(const Token<Corken>& token : lexer.tokens)
            switch(context)
            {
                using enum Corken;
                case General:
                    if(token.kind == identifier)
                    {
                        context = StartNode;
                        unit.id = unit.name = token.symbol(lexer).content;
                        for(const CompilationUnit& prior_unit : units)
                            if(unit.id == prior_unit.id)
                            {
                                Error::log<8uz>(Language::cornea, file, ending(lexer, token),
                                "the compilation unit " + Error::data + unit.id + Error::normal +
                                " starting at " + token.start.stringify() + " already exists at " +
                                prior_unit.start.rangify(prior_unit.end));
                                return std::nullopt;
                            }
                    }
                    else
                    {
                        Error::log<7uz>(Language::cornea, file, ending(lexer, token),
                        "expected the compilation unit identifier, found " + symbol(lexer, token) +
                        Error::normal + " starting at " + token.start.stringify());
                        return std::nullopt;
                    }
                break;
                case StartNode:
                    if(token.kind == sm_start_node)
                    {
                        context = Unit;
                        unit.start = token.start;
                    }
                    else
                    {
                        Error::log<9uz>(Language::cornea, file, ending(lexer, token),
                        "expected the start of the compilation unit " + Error::data + unit.id +
                        Error::normal + " with " + Error::token + '{' + Error::normal + ", found "
                        + symbol(lexer, token) + Error::normal + " starting at " + token.start.
                        stringify());
                        return std::nullopt;
                    }
                break;
                case Unit:
                    switch(token.kind)
                    {
                        case Corken::sm_end_node:
                            for(const CompilationUnit& prior_unit : units)
                                if(unit == prior_unit)
                                {
                                    Error::log<11uz>(Language::cornea, file, ending(lexer, token),
                                    "the compilation unit " + Error::data + unit.id + Error::normal
                                    + " starting at " + unit.start.stringify() +
                                    " is identical to the compilation unit " + Error::data +
                                    prior_unit.id + Error::normal + " at " + prior_unit.start.
                                    rangify(prior_unit.end));
                                    return std::nullopt;
                                }
                            context = General;
                            unit.end = token.start;
                            units.emplace_back(unit);
                        break;
                        case kw_name:
                            context = Name;
                        break;
                        case kw_system:
                            context = System;
                        break;
                        case kw_architecture:
                            context = Architecture;
                        break;
                        case kw_type:
                            context = Type;
                        break;
                        case kw_mode:
                            context = Mode;
                        break;
                        default:
                            Error::log<10uz>(Language::cornea, file, ending(lexer, token),
                            "at the unit " + Error::data + unit.id + Error::normal +
                            " starting at " + unit.start.stringify() + ", expected " + Error::token
                            + "name" + Error::normal +
                            " to assign the project's name of the unit, " + Error::token + "system"
                            + Error::normal + " to assign the target system of the unit, " + Error
                            ::token + "architecture" + Error::normal +
                            " to assign the target architecture of the unit, " + Error::token +
                            "type" + Error::normal +
                            " to assign the project's type of the unit, or " + Error::token +
                            "mode" + Error::normal + " to assign the project's mode, found " +
                            symbol(lexer, token) + Error::normal + " starting at " + token.start.
                            stringify());
                            return std::nullopt;
                    }
                break;
                case Name:
                    switch(subcontext)
                    {
                        case Equal:
                            if(token.kind == sm_equal)
                                subcontext = Value;
                            else
                            {
                                Error::log<12uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + '=' + Error::normal +
                                " to assign the project's name of " + Error::data + unit.id + Error
                                ::normal + ", found " + symbol(lexer, token) + Error::normal +
                                " starting at " + token.start.stringify());
                                return std::nullopt;
                            }
                        break;
                        case Value:
                            if(token.kind == identifier)
                            {
                                subcontext = Sentence;
                                unit.name = token.symbol(lexer).content;
                            }
                            else
                            {
                                Error::log<13uz>(Language::cornea, file, ending(lexer, token),
                                "expected the identifier for the project's name of " + Error::data
                                + unit.id + Error::normal + ", found " + symbol(lexer, token) +
                                Error::normal + " starting at " + token.start.stringify());
                                return std::nullopt;
                            }
                        break;
                        case Sentence:
                            if(token.kind == sm_end_sequence)
                            {
                                context = Unit;
                                subcontext = Equal;
                            }
                            else
                            {
                                Error::log<14uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + ';' + Error::normal +
                                " to end the assignment of the project's name of " + Error::data +
                                unit.id + Error::normal + " starting at " + unit.start.stringify())
                                ;
                                return std::nullopt;
                            }
                    }
                break;
                case System:
                    switch(subcontext)
                    {
                        case Equal:
                            if(token.kind == sm_equal)
                                subcontext = Value;
                            else
                            {
                                Error::log<15uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + '=' + Error::normal +
                                " to assign the target system of " + Error::data + unit.id + Error
                                ::normal + ", found " + symbol(lexer, token) + Error::normal +
                                " starting at " + token.start.stringify());
                                return std::nullopt;
                            }
                        break;
                        case Value:
                            subcontext = Sentence;
                            switch(token.kind)
                            {
                                using enum System;
                                case kw_linux:
                                    unit.system = Linux;
                                break;
                                case kw_darwin:
                                    unit.system = Darwin;
                                break;
                                case kw_windows:
                                    unit.system = Windows;
                                break;
                                default:
                                    Error::log<16uz>(Language::cornea, file, ending(lexer, token),
                                    "expected " + Error::token + "linux" + Error::normal + ", " +
                                    Error::token + "darwin" + Error::normal + ", or " + Error::
                                    token + "windows" + Error::normal +
                                    " as the value of the target system of " + Error::data + unit.
                                    id + Error::normal + ", found " + symbol(lexer, token) + Error
                                    ::normal + " starting at " + token.start.stringify());
                                    return std::nullopt;
                            }
                        break;
                        case Sentence:
                            if(token.kind == sm_end_sequence)
                            {
                                context = Unit;
                                subcontext = Equal;
                            }
                            else
                            {
                                Error::log<17uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + ';' + Error::normal +
                                " to end the assignment of the target system of " + Error::data +
                                unit.id + Error::normal + " starting at " + unit.start.stringify())
                                ;
                                return std::nullopt;
                            }
                    }
                break;
                case Architecture:
                    switch(subcontext)
                    {
                        case Equal:
                            if(token.kind == sm_equal)
                                subcontext = Value;
                            else
                            {
                                Error::log<18uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + '=' + Error::normal +
                                " to assign the target architecture of " + Error::data + unit.id +
                                Error::normal + ", found " + symbol(lexer, token) + Error::normal +
                                " starting at " + token.start.stringify());
                                return std::nullopt;
                            }
                        break;
                        case Value:
                            subcontext = Sentence;
                            switch(token.kind)
                            {
                                using enum Architecture;
                                case kw_amd64:
                                    unit.architecture = Amd64;
                                break;
                                case kw_arm64:
                                    unit.architecture = Arm64;
                                break;
                                case kw_riscv64:
                                    unit.architecture = Riscv64;
                                break;
                                default:
                                    Error::log<19uz>(Language::cornea, file, ending(lexer, token),
                                    "expected " + Error::token + "amd64" + Error::normal + ", " +
                                    Error::token + "arm64" + Error::normal + ", or " + Error::token
                                    + "riscv64" + Error::normal +
                                    " as the value of the target architecture of " + Error::data +
                                    unit.id + Error::normal + ", found " + symbol(lexer, token) +
                                    Error::normal + " starting at " + token.start.stringify());
                                    return std::nullopt;
                            }
                        break;
                        case Sentence:
                            if(token.kind == sm_end_sequence)
                            {
                                context = Unit;
                                subcontext = Equal;
                            }
                            else
                            {
                                Error::log<20uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + ';' + Error::normal +
                                " to end the assignment of the target architecture of " + Error::
                                data + unit.id + Error::normal + " starting at " + unit.start.
                                stringify());
                                return std::nullopt;
                            }
                    }
                break;
                case Type:
                    switch(subcontext)
                    {
                        case Equal:
                            if(token.kind == sm_equal)
                                subcontext = Value;
                            else
                            {
                                Error::log<21uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + '=' + Error::normal +
                                " to assign the project's type of " + Error::data + unit.id + Error
                                ::normal + ", found " + symbol(lexer, token) + Error::normal +
                                " starting at " + token.start.stringify());
                                return std::nullopt;
                            }
                        break;
                        case Value:
                            subcontext = Sentence;
                            switch(token.kind)
                            {
                                using enum Type;
                                case kw_app:
                                    unit.type = App;
                                break;
                                case kw_lib:
                                    unit.type = Lib;
                                break;
                                default:
                                    Error::log<22uz>(Language::cornea, file, ending(lexer, token),
                                    "expected " + Error::token + "app" + Error::normal + " or " +
                                    Error::token + "lib" + Error::normal +
                                    " as the value of the project's type of " + Error::data + unit.
                                    id + Error::normal + ", found " + symbol(lexer, token) + Error
                                    ::normal + " starting at " + token.start.stringify());
                                    return std::nullopt;
                            }
                        break;
                        case Sentence:
                            if(token.kind == sm_end_sequence)
                            {
                                context = Unit;
                                subcontext = Equal;
                            }
                            else
                            {
                                Error::log<23uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + ';' + Error::normal +
                                " to end the assignment of the project's type of " + Error::data +
                                unit.id + Error::normal + " starting at " + unit.start.stringify())
                                ;
                                return std::nullopt;
                            }
                    }
                break;
                case Mode:
                    switch(subcontext)
                    {
                        case Equal:
                            if(token.kind == sm_equal)
                                subcontext = Value;
                            else
                            {
                                Error::log<24uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + '=' + Error::normal +
                                " to assign the project's mode of " + Error::data + unit.id + Error
                                ::normal + ", found " + symbol(lexer, token) + Error::normal +
                                " starting at " + token.start.stringify());
                                return std::nullopt;
                            }
                        break;
                        case Value:
                            subcontext = Sentence;
                            switch(token.kind)
                            {
                                using enum Mode;
                                case kw_debug:
                                    unit.mode = Debug;
                                break;
                                case kw_release:
                                    unit.mode = Release;
                                break;
                                default:
                                    Error::log<25uz>(Language::cornea, file, ending(lexer, token),
                                    "expected " + Error::token + "debug" + Error::normal + " or " +
                                    Error::token + "release" + Error::normal +
                                    " as the value of the project's mode of " + Error::data + unit.
                                    id + Error::normal + ", found " + symbol(lexer, token) + Error
                                    ::normal + " starting at " + token.start.stringify());
                                    return std::nullopt;
                            }
                        break;
                        case Sentence:
                            if(token.kind == sm_end_sequence)
                            {
                                context = Unit;
                                subcontext = Equal;
                            }
                            else
                            {
                                Error::log<26uz>(Language::cornea, file, ending(lexer, token),
                                "expected " + Error::token + ';' + Error::normal +
                                " to end the assignment of the project's mode of " + Error::data +
                                unit.id + Error::normal + " starting at " + unit.start.stringify())
                                ;
                                return std::nullopt;
                            }
                    }
            }
        if(context == General)
        {
            if(units.empty())
            {
                Error::log<28uz>(Language::cornea, file,
                "at least one compilation unit must be provided");
                return std::nullopt;
            }
            debug(file, units);
            return units;
        }
        else
        {
            Error::log<27uz>(Language::cornea, file, "expected " + Error::token + (context not_eq
            StartNode ? "{" : "{}") + Error::normal +
            " before the end of the file to end the definition of the compilation unit " + Error::
            data + unit.id + (context not_eq StartNode ? Error::normal + " starting at " + unit.
            start.stringify() : Error::normal));
            return std::nullopt;
        }
    }
}

#endif