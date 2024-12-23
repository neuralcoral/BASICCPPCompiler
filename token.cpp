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
    if(strcmp(tokenText, "LET") == 0) {
      return new Token("LET", TokenType::LET);
    } else if(strcmp(tokenText, "IF") == 0) {
      return new Token("IF", TokenType::IF);
    } else if (strcmp(tokenText,"THEN") == 0) {
      return new Token("THEN", TokenType::THEN);
    } else if (strcmp(tokenText,"ENDIF") == 0) {
      return new Token("ENDIF", TokenType::ENDIF);
    } else if (strcmp(tokenText,"WHILE") == 0) {
      return new Token("WHILE", TokenType::WHILE);
    } else if (strcmp(tokenText,"REPEAT") == 0) {
      return new Token("REPEAT", TokenType::REPEAT);
    } else if (strcmp(tokenText,"ENDWHILE") == 0) {
      return new Token("ENDWHILE", TokenType::ENDWHILE);
    }
  return nullptr;
}
