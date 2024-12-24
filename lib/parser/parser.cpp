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
  while (checkToken(NEWLINE)) {
    nextToken();
  }

  while (!checkToken(TokenType::END_OF_FILE)) {
    statement();
  }
}

void Parser::expression() {
  std::cout << "EXPRESSION" << std::endl;

  term();
}

void Parser::term() {
  std::cout << "TERM" << std::endl;

  unary();
  while (checkToken(ASTERISK) || checkToken(PLUS)) {
    nextToken();
    unary();
  }
}

void Parser::unary() {
  std::cout << "UNARY" << std::endl;

  if (checkToken(PLUS) || checkToken(MINUS)) {
    nextToken();
  }
  primary();
}

void Parser::primary() {
  std::cout << "PRIMARY (" << currentToken->tokenText << ")\n";

  if (checkToken(NUMBER)) {
    nextToken();
  } else if (checkToken(IDENT)) {
    nextToken();
  } else {
    const auto message = std::string("Unexpected token at '").append(currentToken->tokenText);
    abort(message.c_str());
  }
}


void Parser::comparison() {
  std::cout << "COMPARISON" << std::endl;

  expression();
  if (isComparisonOperator()) {
    nextToken();
    expression();
  } else {
    const auto message = std::string("Expected comparison operator at: '").append(currentToken->tokenText);
    abort(message.c_str());
  }

  while (isComparisonOperator()) {
    nextToken();
    expression();
  }
}

bool Parser::isComparisonOperator() const {
  return checkToken(EQEQ) || checkToken(NOTEQ) || checkToken(GT) || checkToken(GTEQ) || checkToken(LT) || checkToken(LTEQ);
}


void Parser::statement() {
  if (checkToken(TokenType::PRINT)) {
    std::cout << "STATEMENT-PRINT\n";
    nextToken();

    if (checkToken(TokenType::STRING)) {
      nextToken();
    } else {
      std::cout << "EXPRESSION\n";
      nextToken();
    }
  } else if (checkToken(TokenType::IF)) {
    std::cout << "STATEMENT-IF\n";
    nextToken();
    comparison();
    match(THEN);
    newline();
    while (!checkToken(ENDIF)) {
      statement();
    }
    match(ENDIF);
  } else if (checkToken(TokenType::WHILE)) {
    std::cout << "STATEMENT-WHILE\n";
    nextToken();
    comparison();

    match(REPEAT);
    newline();
    while (!checkToken(ENDWHILE)) {
      statement();
    }
    match(ENDWHILE);
  } else if (checkToken(LABEL)) {
    std::cout << "STATEMENT-LABEL\n";
    nextToken();
    match(IDENT);
  } else if (checkToken(GOTO)) {
    std::cout << "STATEMENT-GOTO\n";
    nextToken();
    match(IDENT);
  } else if (checkToken(LET)) {
    std::cout << "STATEMENT-LET\n";
    nextToken();
    match(IDENT);
    match(EQ);
    expression();
  } else if (checkToken(INPUT)) {
    std::cout << "STATEMENT-INPUT\n";
    nextToken();
    match(INPUT);
  } else {
    const auto message = std::string("Invalid statement at ").append(currentToken->tokenText)
    .append(" (").append(toString(currentToken->tokenType)).append(")\n");
    abort(message.c_str());
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
