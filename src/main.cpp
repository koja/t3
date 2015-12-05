#include <cstdlib>

#include "src/t3.hpp"

int main() {
    try {
        t3();
        return EXIT_SUCCESS;

    } catch(...) {
        return EXIT_FAILURE;
    }
}
