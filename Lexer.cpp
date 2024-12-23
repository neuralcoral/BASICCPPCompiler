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
  this->source = new char[sourceLength + 2];
  memcpy(this->source, source, sourceLength);
  this->source[sourceLength] = '\n';
  this->source[sourceLength + 1] = '\0';
  currentChar = source[currentPosition];
}

Lexer::~Lexer() {
  delete[] this->source;
  this->source = nullptr;
}

void Lexer::nextChar() {
  if (currentPosition <= sourceLength) {
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
  if(source[this->currentPosition] == '#') {
    while (currentChar != '\n') {
      nextChar();
    }
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

bool isIllegalStringChar(const char& stringChar) {
  return stringChar == '\r' || stringChar == '\n' || stringChar == '\\' || stringChar == '%';
}

Token* Lexer::handleString() {
  if (currentChar != '"') {
    abort("Not a string");
  }
  nextChar();
  const auto startPosition = currentPosition;
  while (currentChar != '"') {
    if (isIllegalStringChar(currentChar)) {
      abort("Illegal character in string");
    }
    nextChar();
  }
  const unsigned int size = currentPosition - startPosition;
  const auto tokenText = new char[size];
  strncpy(tokenText, source + startPosition, size);
  return new Token(tokenText, STRING);
}

Token* Lexer::handleAlpha() {
  if (!isalpha(currentChar)) {
    abort("Not a alpha character");
  }
  const auto startPosition = currentPosition;
  while (isalnum(peek())) {
    nextChar();
  }
  const unsigned int size = currentPosition - startPosition + 1;
  const auto tokenText = new char[size];
  strncpy(tokenText, source + startPosition, size);
  if (const auto token = Token::tokenMap(tokenText)) {
    return token;
  }

  return new Token(tokenText, IDENT);
}

Token* Lexer::getToken() {
  skipWhitespace();
  skipComment();
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
    case '"':
      token = handleString();
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
      if (isdigit(currentChar)) {
        token = handleNumber();
        break;
      } else if (isalpha(currentChar)) {
        token = handleAlpha();
        break;
      }
      const auto errorMessage = std::string("Unexpected character: `").append(std::string(1, currentChar)).append("`\n");
      abort(errorMessage.c_str());
  }
  nextChar();
  return token;
}


Token* Lexer::handleNumber() {
  if (!isdigit(currentChar)) {
    abort("Not a digit");
  }

  const auto startPosition = currentPosition;
  while (isdigit(peek())) {
    nextChar();
  }
  if (peek() == '.') {
    nextChar();
    if (!isdigit(peek())) {
      abort("Illegal character in number.");
    }
    while (isdigit(peek())) {
      nextChar();
    }
  }
  const unsigned int size = currentPosition - startPosition + 1;
  const auto tokenText = new char[size];
  strncpy(tokenText, source + startPosition, size);
  return new Token(tokenText, NUMBER);
}




void Lexer::abort(const char* message) {
  throw std::runtime_error("Lexing error. " + std::string(message));
}