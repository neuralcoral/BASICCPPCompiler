//
// Created by George Alfaro on 12/17/24.
//

#ifndef LEXER_H
#define LEXER_H
#include "token.h"

class Lexer {
  std::string source;
  char currentChar;
  unsigned int currentPosition;
  unsigned int sourceLength;
  Token* resolveTwoCharacterToken(const char &peekedChar, const TokenType &oneCharType, const TokenType &twoCharType);
  Token* handleString();
  Token* handleNumber();
  Token* handleAlpha();
  public:
    explicit Lexer(const std::string& source);
    Lexer(const Lexer& other);
    void nextChar();
    [[nodiscard]] char peek() const;

    void skipWhitespace();
    void skipComment();
    Token* getToken();
    static void abort(const std::string& message);
};

#endif //LEXER_H
