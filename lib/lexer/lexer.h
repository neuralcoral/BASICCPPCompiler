//
// Created by George Alfaro on 12/17/24.
//

#ifndef LEXER_H
#define LEXER_H
#include "token.h"

class Lexer {
  char *source;
  char currentChar;
  unsigned int currentPosition;
  unsigned int sourceLength;
  Token* resolveTwoCharacterToken(const char &peekedChar, const TokenType &oneCharType, const TokenType &twoCharType);
  Token* handleString();
  Token* handleNumber();
  Token* handleAlpha();
  public:
    explicit Lexer(const char* source);
    Lexer(const Lexer& other);
    ~Lexer();
    void nextChar();
    [[nodiscard]] char peek() const;

    void skipWhitespace();
    void skipComment();
    Token* getToken();
    static void abort(const char *message);
};

#endif //LEXER_H
