//
// Created by George Alfaro on 12/17/24.
//

#include "token.h"
#include <cstring>

Token::Token() {
  this->tokenText = new char[1];
  this->tokenText[0] = '\0';
  this->tokenType = END_OF_FILE;
}

Token::Token(const char* tokenText, const TokenType& tokenType) {
  this->tokenText = new char[strlen(tokenText) + 1];
  memcpy(this->tokenText, tokenText, strlen(tokenText));
  this->tokenText[strlen(tokenText)] = '\0';
  this->tokenType = tokenType;
}

Token::Token(const char& tokenStart, const TokenType& tokenType) {
  tokenText = new char[2];
  tokenText[0] = tokenStart;
  tokenText[1] = '\0';
  this->tokenType = tokenType;
}

Token::~Token() {
  delete[] tokenText;
  tokenText = nullptr;
}

Token* Token::tokenMap(const char* tokenText) {
    if (strcmp(tokenText, toString(LABEL)) == 0) {
      return new Token(tokenText, LABEL);
    } else if(strcmp(tokenText, toString(GOTO)) == 0) {
      return new Token(tokenText, GOTO);
    } else if(strcmp(tokenText, toString(PRINT)) == 0) {
      return new Token(tokenText, PRINT);
    } else if(strcmp(tokenText, toString(INPUT)) == 0) {
      return new Token(tokenText, INPUT);
    } else if(strcmp(tokenText, toString(LET)) == 0) {
      return new Token(tokenText, LET);
    } else if(strcmp(tokenText, toString(IF)) == 0) {
      return new Token(tokenText, TokenType::IF);
    } else if (strcmp(tokenText, toString(THEN)) == 0) {
      return new Token(tokenText, TokenType::THEN);
    } else if (strcmp(tokenText, toString(ENDIF)) == 0) {
      return new Token(tokenText, TokenType::ENDIF);
    } else if (strcmp(tokenText, toString(WHILE)) == 0) {
      return new Token(tokenText, TokenType::WHILE);
    } else if (strcmp(tokenText, toString(REPEAT)) == 0) {
      return new Token(tokenText, TokenType::REPEAT);
    } else if (strcmp(tokenText, toString(ENDWHILE)) == 0) {
      return new Token(tokenText, TokenType::ENDWHILE);
    }
  return nullptr;
}
