#include "tacc.h"

#include <iostream>

namespace tacc {

bool Lexer::isAtEnd() { return current >= source.length(); }

void Lexer::scanToken() {
  char c = advance();

  switch (c) {
  case '(':
    addToken(L_PAREN);
    break;
  case ')':
    addToken(R_PAREN);
    break;
  case '{':
    addToken(L_BRACE);
    break;
  case '}':
    addToken(R_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(PERIOD);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(ASTERISK);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;
  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd())
        advance();
    } else {
      addToken(FSLASH);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    onString();
    break;
  default:
    Tacc::error(line, "Unexpected Character.");
    break;
  }
}

char Lexer::advance() { return source.at(current++); }

void Lexer::addToken(tokenType type) { addToken(type, NULL); }

void Lexer::addToken(tokenType type, std::string literal) {
  std::string text = source.substr(start, current - start);
  auto token = std::make_unique<Token>(type, text, literal, line);
  tokens.push_back(std::move(token));
}

bool Lexer::match(char expected) {
  if (isAtEnd())
    return false;

  if (source.at(current) != expected)
    return false;

  current++;
  return true;
}

char Lexer::peek() {
  if (isAtEnd())
    return '\0';
  return source.at(current);
}

void Lexer::onString() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') {
      Tacc::error(line, "Multi-line strings aren't supported.");
      return;
    }
    advance();
  }

  if (isAtEnd()) {
    Tacc::error(line, "Unterminated String.");
    return;
  }

  advance();

  addToken(STRING, source.substr(start + 1, current - start - 1));
}

// public

Lexer::Lexer(std::string source) { this->source = source; }

std::list<std::unique_ptr<Token>> Lexer::lexTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  auto token = std::make_unique<Token>(END, "", "", line);
  tokens.push_back(std::move(token));
  return std::move(tokens);
}

} // namespace tacc
