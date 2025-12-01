#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Position.hpp"
#include "Error.hpp"

namespace Iris
{
    [[nodiscard]] auto Position::stringify(const bool coloured) const noexcept -> std::string
    {
        if(coloured)
            return Error::numeric + std::to_string(line) + Error::token + " : " + Error::numeric +
            std::to_string(column) + Error::normal;
        return std::to_string(line) + " : " + std::to_string(column);
    }

    [[nodiscard]] auto Position::rangify(const Position end, const bool coloured) const noexcept ->
    std::string
    {
        if(coloured)
            return Error::token + '[' + stringify() + Error::token + ", " + end.stringify() + Error
            ::token + ']' + Error::normal;
        return '[' + stringify(false) + ", " + end.stringify(false) + ']';
    }
}

#endif