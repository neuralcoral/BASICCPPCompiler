//
// Created by George Alfaro on 12/17/24.
//

#ifndef TOKEN_H
#define TOKEN_H
#include "token_type.h"
struct Token {
  char* tokenText;
  TokenType tokenType;

  Token();
  Token(const char* tokenText, const TokenType& tokenType);
  Token(const char tokenStart, const TokenType& tokenType);
  ~Token();
};

#endif //TOKEN_H
