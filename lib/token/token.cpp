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

Token::Token(const std::string& tokenText, const TokenType& tokenType) {
  this->tokenText = tokenText;
  this->tokenType = tokenType;
}

Token::Token(const char& tokenStart, const TokenType& tokenType) {
  tokenText = new char[2];
  tokenText[0] = tokenStart;
  tokenText[1] = '\0';
  this->tokenType = tokenType;
}

Token* Token::tokenMap(const std::string tokenText) {
    if (tokenText == toString(LABEL)) {
      return new Token(tokenText, LABEL);
    } else if(tokenText  == toString(GOTO)) {
      return new Token(tokenText, GOTO);
    } else if(tokenText  == toString(PRINT)) {
      return new Token(tokenText, PRINT);
    } else if(tokenText  == toString(INPUT)) {
      return new Token(tokenText, INPUT);
    } else if(tokenText  == toString(LET)) {
      return new Token(tokenText, LET);
    } else if(tokenText  == toString(IF)) {
      return new Token(tokenText, TokenType::IF);
    } else if (tokenText  == toString(THEN)) {
      return new Token(tokenText, TokenType::THEN);
    } else if (tokenText  == toString(ENDIF)) {
      return new Token(tokenText, TokenType::ENDIF);
    } else if (tokenText  == toString(WHILE)) {
      return new Token(tokenText, TokenType::WHILE);
    } else if (tokenText  == toString(REPEAT)) {
      return new Token(tokenText, TokenType::REPEAT);
    } else if (tokenText  == toString(ENDWHILE)) {
      return new Token(tokenText, TokenType::ENDWHILE);
    }
  return nullptr;
}
