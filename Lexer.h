//
// Created by George Alfaro on 12/17/24.
//

#ifndef LEXER_H
#define LEXER_H
#include "token.h"

class Lexer {
  private:
    char* source;
    char currentChar;
    unsigned int currentPosition;
    unsigned int sourceLength;
  public:
    Lexer(const char* source);
    ~Lexer();
    void nextChar();
    char peek() const;
    void abort() const;
    void skipWhitespace();
    void skipComment();
    Token getToken();
};



#endif //LEXER_H
