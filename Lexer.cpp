//
// Created by George Alfaro on 12/17/24.
//

#include "lexer.h"
#include <string.h>
#include <stdexcept>
#include <sstream>
#include "token.h"
#include "token_type.h"

Lexer::Lexer(const char* source) {
  currentPosition = 0;
  sourceLength = strlen(source);
  if (sourceLength == 0) {
    source = nullptr;
    currentChar = '\0';
    return;
  }
  this->source = new char[sourceLength + 1];
  memcpy(this->source, source, sourceLength);
  this->source[sourceLength] = '\0';
  currentChar = source[currentPosition];
}

Lexer::~Lexer() {
  delete[] this->source;
  this->source = nullptr;
}

void Lexer::nextChar() {
  if (currentPosition < sourceLength) {
    currentChar = source[currentPosition];
  }
}

char Lexer::peek() const {
  if (this->currentPosition >= this->source[this->currentPosition]) {
    return '\0';
  }
  return this->source[this->currentPosition + 1];
}

void Lexer::skipWhitespace() {
  while(std::isspace(source[this->currentPosition])) {
    nextChar();
  }
}
void Lexer::skipComment() {
  while(source[this->currentPosition] == '#') {
    nextChar();
  }
}

Token Lexer::getToken() {
  Token token;
  switch(currentChar) {
    case '+':
      token = Token(currentChar, TokenType::PLUS);
      break;
    case '-':
      token = Token(currentChar, TokenType::MINUS);
      break;
    case '*':
      token = Token(currentChar, TokenType::ASTERISK);
      break;
    case '/':
      token = Token(currentChar, TokenType::SLASH);
      break;
    case '\n':
      token = Token(currentChar, TokenType::NEWLINE);
      break;
    case '\0':
      token = Token(currentChar, TokenType::END_OF_FILE);
      break;
    default:
  }
  nextChar();
  return token;
}

void Lexer::abort() const {
  throw std::runtime_error("Lexer abort");
}