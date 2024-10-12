#include "tacc.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <list>

namespace tacc {


Token::Token(tokenType type, std::string lexeme, std::any literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

static std::string typeToString(tokenType type) {
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
            break;
        case BANG:
            return "BANG";
            break;
        case BANG_EQUAL:
            return "BANG_EQUAL";
            break;
        case EQUAL:
            return "EQUAL";
            break;
        case EQUAL_EQUAL:
            return "EQUAL_EQUAL";
            break;
        case GREATER:
            return "GREATER";
            break;
        case GREATER_EQUAL:
            return "GREATER_EQUAL";
            break;
        case LESS:
            return "LESS";
            break;
        case LESS_EQUAL:
            return "LESS_EQUAL";
            break;
        case IDENTIFIER:
            return "IDENTIFIER";
            break;
        case STRING:
            return "STRING";
            break;
        case NUMBER:
            return "NUMBER";
            break;
        case IF:
            return "IF";
            break;
        case ELSE:
            return "ELSE";
            break;
        case RETURN:
            return "RETURN";
            break;
        case DO:
            return "DO";
            break;
        case WHILE:
            return "WHILE";
            break;
        case END:
            return "END";
            break;
    }
}

std::string Token::toString() {
    std::stringstream ss;
    ss << "Token: {type: " << typeToString(type) << ", lexeme: " << lexeme << ", literal: TODO, line: " << line << "}" << std::endl;
    return ss.str();
}

void Tacc::runFile(std::string filename) {
    std::ifstream file {filename};
    std::string buffer {std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};
    return run(buffer);
}

void Tacc::run(std::string source) {
    std::unique_ptr<Lexer> lexer(new Lexer(source));

    std::list<std::unique_ptr<Token>> tokens = lexer->lexTokens();

    for (std::unique_ptr<Token>& token : tokens)
        std::cout << "test" << std::endl;

}

void Tacc::error(int line, std::string message) {
    return report(line, "", message);
}

void Tacc::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}


bool Lexer::isAtEnd() {
    return current >= source.length();
}

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
        default:
            Tacc::error(line, "Unexpected Character.");
            break;
    }
}

char Lexer::advance() {
    return source.at(current++);
}

void Lexer::addToken(tokenType type) {
    addToken(type, NULL);
}

void Lexer::addToken(tokenType type, std::any literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(std::unique_ptr<Token>{new Token(type, text, literal, line)});
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

Lexer::Lexer(std::string source) {
    this->source = source;
}

std::list<std::unique_ptr<Token>> Lexer::lexTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(std::unique_ptr<Token> {new Token(END, "", NULL, line)});
    return tokens;
}

}


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
