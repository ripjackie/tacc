#include "tacc.h"

#include <fstream>
#include <iostream>
#include <list>
#include <memory>

namespace tacc {

void Tacc::runFile(std::string filename) {
  std::ifstream file{filename};
  std::string buffer{std::istreambuf_iterator<char>{file},
                     std::istreambuf_iterator<char>{}};
  return run(buffer);
}

void Tacc::run(std::string source) {
  std::unique_ptr<Lexer> lexer(new Lexer(source));

  std::list<std::unique_ptr<Token>> tokens = lexer->lexTokens();

  for (std::unique_ptr<Token> &token : tokens)
    std::cout << token->toString() << std::endl;
}

void Tacc::error(int line, std::string message) {
  return report(line, "", message);
}

void Tacc::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << line << "] Error " << where << ": " << message
            << std::endl;
  exit(EXIT_FAILURE);
}

} // namespace tacc

int main(int argc, char **argv) {

  std::unique_ptr<tacc::Tacc> tacc{new tacc::Tacc};

  if (argc > 2 || argc == 1) {
    std::cerr << "Usage: " << argv[0] << " <inputfile>" << std::endl;
    return 1;
  } else {
    tacc->runFile(argv[1]);
    return 0;
  }
}
