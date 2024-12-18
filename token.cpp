//
// Created by George Alfaro on 12/17/24.
//

#include "token.h"
#include <string.h>

Token::Token() {
  this->tokenText = new char[1];
  this->tokenText[0] = '\0';
  this->tokenType = TokenType::END_OF_FILE;
}

Token::Token(const char* tokenText, const TokenType& tokenType) {
  this->tokenText = new char[strlen(tokenText) + 1];
  memcpy(this->tokenText, tokenText, strlen(tokenText));
  this->tokenText[strlen(tokenText)] = '\0';
  this->tokenType = tokenType;
}

Token::Token(const char tokenText, const TokenType& tokenType) {
  this->tokenText = new char[2];
  this->tokenText[0] = tokenText;
  this->tokenText[1] = '\0';
  this->tokenType = tokenType;
}

Token::~Token() {
  delete[] tokenText;
  tokenText = nullptr;
}