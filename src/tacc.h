#ifndef  TACC_H_
#define TACC_H_

#include <string>

namespace tacc {

class Tacc {

    static void run(std::string buffer);

    public:
    static void runFile(std::string filename);

};

}

#endif // TACC_H_
