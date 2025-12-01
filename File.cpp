#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "File.hpp"
#include <fstream>
#include <filesystem>

namespace Iris::File
{
    [[nodiscard]] auto log(const std::string& file) noexcept -> std::string
    {
        std::string tt_file = file;
        for(std::size_t x = file.size() - 1uz; x > 0uz and file[x] not_eq '.'; --x)
            tt_file.pop_back();
        tt_file += "log";
        return tt_file;
    }

    [[nodiscard]] auto token_tree(const std::string& file) noexcept -> std::string
    {
        std::string tt_file = file;
        for(std::size_t x = file.size() - 1uz; x > 0uz and file[x] not_eq '.'; --x)
            tt_file.pop_back();
        tt_file += "tt";
        return tt_file;
    }

    [[nodiscard]] auto units_tree(const std::string& file) noexcept -> std::string
    {
        std::string cu_file = file;
        for(std::size_t x = file.size() - 1uz; x > 0uz and file[x] not_eq '.'; --x)
            cu_file.pop_back();
        cu_file += "cut";
        return cu_file;
    }

    [[nodiscard]] auto iris_abstract_tree(const std::string& file) noexcept -> std::string
    {
        std::string iat_file = file;
        for(std::size_t x = file.size() - 1uz; x > 0uz and file[x] not_eq '.'; --x)
            iat_file.pop_back();
        iat_file += "iat";
        return iat_file;
    }

    [[nodiscard]] auto lens_intermediate_representation(const std::string& file) noexcept -> std::
    string
    {
        std::string lir_file = file;
        for(std::size_t x = file.size() - 1uz; x > 0uz and file[x] not_eq '.'; --x)
            lir_file.pop_back();
        lir_file += "lir";
        return lir_file;
    }

    [[nodiscard]] auto read(const std::string& file) noexcept -> std::string
    {
        std::string content;
        const std::size_t size = std::filesystem::file_size(file);
        content.resize(size, '\0');
        std::ifstream(file, std::ios_base::binary).read(content.data(), size);
        return content;
    }

    auto write_text(const std::string& file, const std::string& content) noexcept -> void
    {
        std::ofstream(file).write(content.c_str(), content.size());
    }

    auto write(const std::string& file, const std::string& content) noexcept -> void
    {
        std::ofstream(file, std::ios_base::binary).write(content.c_str(), content.size());
    }
}

#endif