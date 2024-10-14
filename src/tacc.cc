#include "tacc.h"

#include <iostream>
#include <fstream>

namespace tacc {

void Tacc::runFile(std::string filename) {
    std::ifstream file {filename};
    std::string buffer {std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};
    return run(buffer);
}

void Tacc::run(std::string buffer) {
}


int main(int argc, char **argv) {

    if (argc > 2 || argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <inputfile>" << std::endl;
        return 1;
    } else {
        tacc::Tacc::runFile(argv[1]);
        return 0;
    }

}
