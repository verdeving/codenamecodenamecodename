#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#ifndef iris_guard_core_sets
#define iris_guard_core_sets
#include <string>
#define $digit_non_zero '1': case '2': case '3': case '4': case '5': case '6': case '7': case \
'8': case '9'
#define $digit '0': case $digit_non_zero
#define $uppercase 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case\
 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': \
case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z'
#define $lowercase 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case\
 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': \
case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z'
#define $alpha $uppercase: case $lowercase
#define $alphanumeric $digit: case $alpha
#define $whitespace '\f': case '\v': case '\t': case '\r': case '\n': case ' '

namespace Iris
{
    [[nodiscard]] auto map(const char character) noexcept -> std::string;
}

#endif
#endif