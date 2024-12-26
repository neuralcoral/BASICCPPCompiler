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

Lexer::Lexer(const std::string& source) {
  currentPosition = 0;
  sourceLength = source.size();
  if (sourceLength == 0) {
    currentChar = '\0';
    return;
  }
  this->source = source;
  this->source.append(1, '\n');
  currentChar = source[currentPosition];
}

Lexer::Lexer(const Lexer& other) {
  currentPosition = other.currentPosition;
  sourceLength = other.sourceLength;
  source = other.source;
  currentChar = other.currentChar;
}

void Lexer::nextChar() {
  if (currentPosition <= sourceLength) {
    currentChar = source[++currentPosition];
  }
}

char Lexer::peek() const {
  if (this->currentPosition >= this->sourceLength) {
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
  auto finalStr = std::string(1, firstChar);
  finalStr.push_back(secondChar);
  return new Token(finalStr, type);
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
  return new Token(source.substr(startPosition, size), STRING);
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
  const auto tokenText = source.substr(startPosition, size);
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
        abort(std::string("Expected '!=', got `!").append(std::string(1, peek())).append("`\n"));
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
      abort(errorMessage);
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
  return new Token(source.substr(startPosition, size), NUMBER);
}




void Lexer::abort(const std::string& message) {
  throw std::runtime_error("Lexing error. " + std::string(message));
}