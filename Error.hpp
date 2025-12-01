#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_error
#define iris_guard_core_error
#include "File.hpp"
#include "Language.hpp"
#include "../Cornea/CompilationUnit.hpp"
#include <print>
#include <iostream>

namespace Iris::Error
{
    #ifdef iris_debug
    inline constexpr std::string normal, bold, italic, error, path, data, numeric, token;
    #else
    inline constexpr std::string normal = "\033[0m", bold = "\033[1m", italic = "\033[3m", error =
    "\033[31m", path = "\033[32m", data = "\033[34m", numeric = "\033[35m", token = "\033[36m";
    #endif

    template<std::size_t code> requires(code > 0uz) auto log(const Language language, const std::
    string message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text("general.log", "iris: error(" + stringify(language) + std::to_string(code)
        + ") -> " + message);
        #else
        std::println(std::cerr, "{}{}iris:{} {}error{}({}{}{}{}{}) ->{} {}", bold, italic, normal,
        error, token, data, stringify(language), numeric, std::to_string(code), token, normal,
        message);
        #endif
    }

    template<std::size_t code> requires(code > 0uz) auto log(const Language language, const Cornea
    ::CompilationUnit& unit, const std::string message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text("general.log", "iris: error(" + stringify(language) + std::to_string(code)
        + ") -> " + message);
        #else
        std::println(std::cerr, "{}{}iris:{} {}error{}({}{}{}{}{}) {}in the unit {}{}{} ->{} {}",
        bold, italic, normal, error, token, data, stringify(language), numeric, std::to_string(code
        ), token, normal, data, unit.id, token, normal, message);
        #endif
    }

    template<std::size_t code> requires(code > 0uz) auto log(const Language language, const std::
    string& file, const std::string message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text(File::log(file), "iris: error(" + stringify(language) + std::to_string(
        code) + ") @ " + file + " -> " + message);
        #else
        std::println(std::cerr, "{}{}iris:{} {}error{}({}{}{}{}{}) @ {}{}{}{}{} ->{} {}", bold,
        italic, normal, error, token, data, stringify(language), numeric, std::to_string(code),
        token, italic, path, file, normal, token, normal, message);
        #endif
    }

    template<std::size_t code> requires(code > 0uz) auto log(const Language language, const std::
    string& file, const Cornea::CompilationUnit& unit, const std::string message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text(File::log(file), "iris: error(" + stringify(language) + std::to_string(
        code) + ") @ " + file + " in the unit " + unit.id + " -> " + message);
        #else
        std::println(std::cerr,
        "{}{}iris:{} {}error{}({}{}{}{}{}) @ {}{}{}{} in the unit{} {}{} ->{} {}", bold, italic,
        normal, error, token, data, stringify(language), numeric, std::to_string(code), token,
        italic, path, file, normal, data, unit.id, token, normal, message);
        #endif
    }

    template<std::size_t code> requires(code > 0uz) auto log(const Language language, const std::
    string& file, const Position& position, const std::string message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text(File::log(file), "iris: error(" + stringify(language) + std::to_string(
        code) + ") @ " + file + " : " + position.stringify() + " -> " + message);
        #else
        std::println(std::cerr,
        "{}{}iris:{} {}error{}({}{}{}{}{}) @ {}{}{}{}{} : {}{}{} : {}{} {}->{} {}", bold, italic,
        normal, error, token, data, stringify(language), numeric, std::to_string(code), token,
        italic, path, file, normal, token, numeric, position.line, token, numeric, position.column,
        token, normal, message);
        #endif
    }

    template<std::size_t code> requires(code > 0uz) auto log(const Language language, const std::
    string& file, const Position& position, const Cornea::CompilationUnit& unit, const std::string
    message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text(File::log(file), "iris: error(" + stringify(language) + std::to_string(
        code) + ") @ " + file + " : " + position.stringify() + " in the unit " + unit.id + " -> " +
        message);
        #else
        std::println(std::cerr,
        "{}{}iris:{} {}error{}({}{}{}{}{}) @ {}{}{}{}{} : {}{}{} : {}{} {}in the unit {}{} {}->{} "
        "{}", bold, italic, normal, error, token, data, stringify(language), numeric, std::
        to_string(code), token, italic, path, file, normal, token, numeric, position.line, token,
        numeric, position.column, normal, data, unit.id, token, normal, message);
        #endif
    }

    auto log(const std::string& file, const std::string message) noexcept -> void;
}

#endif
#endif