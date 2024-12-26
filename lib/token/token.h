//
// Created by George Alfaro on 12/17/24.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <string>

#include "token_type.h"
struct Token {
  std::string tokenText;
  TokenType tokenType;

  Token();
  Token(const std::string& tokenText, const TokenType& tokenType);
  Token(const char& tokenStart, const TokenType& tokenType);

  static Token* tokenMap(std::string tokenText);
};

#endif //TOKEN_H
