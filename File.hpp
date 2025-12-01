#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_file
#define iris_guard_core_file
#include <string>

namespace Iris::File
{
    [[nodiscard]] auto log(const std::string& file) noexcept -> std::string;

    [[nodiscard]] auto token_tree(const std::string& file) noexcept -> std::string;

    [[nodiscard]] auto units_tree(const std::string& file) noexcept -> std::string;

    [[nodiscard]] auto iris_abstract_tree(const std::string& file) noexcept -> std::string;

    [[nodiscard]] auto lens_intermediate_representation(const std::string& file) noexcept -> std::
    string;

    [[nodiscard]] auto read(const std::string& file) noexcept -> std::string;

    auto write_text(const std::string& file, const std::string& content) noexcept -> void;

    auto write(const std::string& file, const std::string& content) noexcept -> void;
}

#endif
#endif