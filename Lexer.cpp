//
// Created by George Alfaro on 12/17/24.
//

#include "lexer.h"
#include <cstring>
#include <stdexcept>
#include <sstream>
#include "token.h"
#include "token_type.h"

bool isWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\r';
}

Lexer::Lexer(const char* source) {
  currentPosition = 0;
  sourceLength = strlen(source);
  if (sourceLength == 0) {
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
    currentChar = source[++currentPosition];
  }
}

char Lexer::peek() const {
  if (this->currentPosition >= this->source[this->currentPosition]) {
    return '\0';
  }
  return this->source[this->currentPosition + 1];
}

void Lexer::skipWhitespace() {
  while(isWhitespace(source[this->currentPosition])) {
    nextChar();
  }
}

void Lexer::skipComment() {
  while(source[this->currentPosition] == '#') {
    nextChar();
  }
}

Token* buildTwoCharacterToken(const char& firstChar, const char& secondChar, const TokenType& type) {
  const auto chars = new char[2];
  chars[0] = firstChar; chars[1] = secondChar;
  return new Token(chars, type);
}
Token* Lexer::resolveTwoCharacterToken(const char& peekedChar, const TokenType& oneCharType, const TokenType& twoCharType) {
  Token* token = nullptr;
  if (peek() == peekedChar) {
    const auto firstChar = currentChar;
    nextChar();
    const auto secondChar = currentChar;
    token = buildTwoCharacterToken(firstChar, secondChar, twoCharType);
  } else {
    token = new Token(currentChar, oneCharType);
  }
  return token;
}

Token* Lexer::getToken() {
  skipWhitespace();
  Token* token = nullptr;
  switch(currentChar) {
    case '+':
      token = new Token(currentChar, TokenType::PLUS);
      break;
    case '-':
      token = new Token(currentChar, TokenType::MINUS);
      break;
    case '*':
      token = new Token(currentChar, TokenType::ASTERISK);
      break;
    case '/':
      token = new Token(currentChar, TokenType::SLASH);
      break;
    case '\n':
      token = new Token(currentChar, TokenType::NEWLINE);
      break;
    case '\0':
      token = new Token(currentChar, TokenType::END_OF_FILE);
      break;
    case '=':
      token = resolveTwoCharacterToken('=', EQ, EQEQ);
      break;
    case '>':
      token = resolveTwoCharacterToken('=', GT, GTEQ);
      break;
    case '<':
      token = resolveTwoCharacterToken('=', LT, LTEQ);
      break;
    case '!':
      if (peek() == '=') {
        nextChar();
        token = buildTwoCharacterToken('!','=', NOTEQ);
      } else {
        abort(std::string("Expected '!=', got `!").append(std::string(1, peek())).append("`\n").c_str());
      }
      break;
    default:
      const auto errorMessage = std::string("Unexpected character: `").append(std::string(1, currentChar)).append("`\n");
      abort(errorMessage.c_str());
  }
  nextChar();
  return token;
}

void Lexer::abort(const char* message) {
  throw std::runtime_error("Lexing error. " + std::string(message));
}