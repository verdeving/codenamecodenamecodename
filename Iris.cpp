#if iris_major >= 0 and iris_middle >= 0 and iris_minor >= 1
#include "Core/CLI.hpp"

int main(int argc, char** argv)
{
    #ifdef iris_lsp
    #else
    Iris::CLI::process(argc, argv);
    #endif
}

#endif