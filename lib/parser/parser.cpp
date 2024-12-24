//
// Created by George Alfaro on 12/23/24.
//

#include "parser.h"

#include <iostream>


Parser::Parser(Lexer * lexer) : lexer(lexer) {
  currentToken = nullptr;
  peekToken = nullptr;
  nextToken();
  nextToken();
}

bool Parser::checkToken(const TokenType& tokenType) const {
  return tokenType == currentToken->tokenType;
}

bool Parser::checkPeek(const TokenType& tokenType) const {
  return tokenType == peekToken->tokenType;
}

void Parser::abort(const char* message) {
  std::cerr << message << std::endl;
  throw std::runtime_error(message);
}

void Parser::match(const TokenType& tokenType) {
  if (!checkToken(tokenType)) {
    const auto tokenTypeString = std::string(toString(tokenType));
    const auto currentTokenTypeString = std::string(toString(currentToken->tokenType));
    const auto message = std::string("Expected token type '").append(tokenTypeString)
                             .append("'. Received '").append(currentTokenTypeString).append("'.\n");
    abort(message.c_str());
  }
  nextToken();
}

void Parser::nextToken() {
  delete currentToken;
  currentToken = peekToken;
  peekToken = lexer->getToken();
}

void Parser::program() {
  std::cout << "PROGRAM" << std::endl;

  while (!checkToken(TokenType::END_OF_FILE)) {
    statement();
  }
}

void Parser::statement() {
  if (checkToken(TokenType::PRINT)) {
    std::cout << "STATEMENT-PRINT\n";
    nextToken();

    if (checkToken(TokenType::STRING)) {
      std::cout << "STATEMENT-STRING\n";
    } else {
      std::cout << "EXPRESSION\n";
    }
  }
  newline();
}

void Parser::newline() {
  std::cout << "NEWLINE" << std::endl;
  match(TokenType::NEWLINE);
  while (checkToken(TokenType::NEWLINE)) {
    nextToken();
  }
}
