#include <iostream>

#include "TestExtins.h"
#include "TestScurt.h"

int main(int argc, char **argv) {
    testAll();
    testAllExtins();

    std::cout << "All tests ran successfully.\n";
    return 0;
}
