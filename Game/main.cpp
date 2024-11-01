#include "main.hpp"

#include <cmath>
#include <raylib.h>
#include <stdexcept>

EXPORT_LIB void libmain(void* args, size_t argc) {
    if(argc == 0) throw std::runtime_error("Hot Reload Library missing arguments");

    ClearBackground(BLACK); // Try changing this value
}