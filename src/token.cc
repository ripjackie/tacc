#include "tacc.h"

#include <sstream>

namespace tacc {

Token::Token(tokenType type, std::string lexeme, std::string literal,
             int line) {
  this->type = type;
  this->lexeme = lexeme;
  this->literal = literal;
  this->line = line;
}

Token::~Token() {}

std::string Token::typeToString(tokenType type) {
  switch (type) {
  case L_PAREN:
    return "L_PAREN";
  case R_PAREN:
    return "R_PAREN";
  case L_BRACE:
    return "L_BRACE";
  case R_BRACE:
    return "R_BRACE";
  case COMMA:
    return "COMMA";
  case PERIOD:
    return "PERIOD";
  case MINUS:
    return "MINUS";
  case PLUS:
    return "PLUS";
  case SEMICOLON:
    return "SEMICOLON";
  case FSLASH:
    return "FSLASH";
  case ASTERISK:
    return "ASTERISK";
  case BANG:
    return "BANG";
  case BANG_EQUAL:
    return "BANG_EQUAL";
  case EQUAL:
    return "EQUAL";
  case EQUAL_EQUAL:
    return "EQUAL_EQUAL";
  case GREATER:
    return "GREATER";
  case GREATER_EQUAL:
    return "GREATER_EQUAL";
  case LESS:
    return "LESS";
  case LESS_EQUAL:
    return "LESS_EQUAL";
  case IDENTIFIER:
    return "IDENTIFIER";
  case STRING:
    return "STRING";
  case NUMBER:
    return "NUMBER";
  case IF:
    return "IF";
  case ELSE:
    return "ELSE";
  case RETURN:
    return "RETURN";
  case DO:
    return "DO";
  case WHILE:
    return "WHILE";
  case END:
    return "END";
  default:
    return "UNDEFINED TOKEN";
  }
}

std::string Token::toString() {
  std::stringstream ss;
  ss << "{";
  ss << " \"type\": \"" << Token::typeToString(this->type) << "\",";
  ss << " \"lexeme\": \"" << lexeme << "\",";
  ss << " \"literal\": \"TODO\"";
  ss << " \"literal\": \"" << literal << "\',";
  ss << " \"line\": \"" << line << "\"";
  ss << "}";
  return ss.str();
}

} // namespace tacc
