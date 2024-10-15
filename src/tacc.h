#ifndef TACC_H_
#define TACC_H_

#include <any> // Needed??
#include <list>
#include <memory>
#include <string>

namespace tacc {

typedef enum tokenType {
  L_PAREN,
  R_PAREN,
  L_BRACE,
  R_BRACE,
  COMMA,
  PERIOD,
  MINUS,
  PLUS,
  SEMICOLON,
  FSLASH,
  ASTERISK,

  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  IDENTIFIER,
  STRING,
  NUMBER,

  IF,
  ELSE,
  RETURN,
  DO,
  WHILE,

  END
} tokenType;

struct Token {
  tokenType type;
  std::string lexeme;
  std::string literal;
  // std::any literal; // Better way??
  int line;

  static std::string typeToString(tokenType type);

public:
  Token(tokenType type, std::string lexeme, std::string literal, int line);
  ~Token();
  std::string toString();
};

class Tacc {
  static void run(std::string buffer);

public:
  static void runFile(std::string filename);
  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string message);
};

class Lexer {
  int start{0};
  int current{0};
  int line{1};
  std::string source;
  std::list<std::unique_ptr<Token>> tokens;

  bool isAtEnd();
  void scanToken();
  char advance();
  void addToken(tokenType type);
  void addToken(tokenType type, std::string literal);
  bool match(char expected);
  char peek();
  void onString();

public:
  Lexer(std::string source);

  std::list<std::unique_ptr<Token>> lexTokens();
};

} // namespace tacc

#endif // TACC_H_
