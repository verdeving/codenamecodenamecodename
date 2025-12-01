#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Error.hpp"

namespace Iris::Error
{
    auto log(const std::string& file, const std::string message) noexcept -> void
    {
        #ifdef iris_debug
        File::write_text(File::log(file), "iris: error @ " + file + " -> " + message);
        #else
        std::println(std::cerr, "{}{}iris:{} {}error{} @ {}{}{}{}{} -> {}{}", bold, italic, normal,
        error, token, italic, path, file, normal, token, normal, message);
        #endif
    }
}

#endif