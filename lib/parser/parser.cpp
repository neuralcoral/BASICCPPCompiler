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

void Parser::abort(const std::string message) {
  std::cerr << message << std::endl;
  throw std::runtime_error(message);
}

void Parser::match(const TokenType& tokenType) {
  if (!checkToken(tokenType)) {
    const auto tokenTypeString = std::string(toString(tokenType));
    const auto currentTokenTypeString = std::string(toString(currentToken->tokenType));
    const auto message = std::string("Expected token type '").append(tokenTypeString)
                             .append("'. Received '").append(currentTokenTypeString).append("'.\n");
    abort(message);
  }
  nextToken();
}

void Parser::nextToken() {
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

  for (const auto& label : labelsGotoed) {
    if (!labelsDeclared.contains(label)) {
      const auto message = std::string("Attempting to GOTO to undeclared label: '").append(label).append("'.\n");
      abort(message);
    }
  }
}

void Parser::expression() {
  std::cout << "EXPRESSION" << std::endl;

  term();
  while (checkToken(PLUS) || checkToken(MINUS)) {
    nextToken();
    term();
  }
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
  if (checkToken(NUMBER)) {
    std::cout << "PRIMARY (" << currentToken->tokenText << ")\n";
    nextToken();
  } else if (checkToken(IDENT)) {
    if (!symbols.contains(currentToken->tokenText)) {
      abort("Referencing variable before assignment: " + currentToken->tokenText);
    }
    std::cout << "PRIMARY (" << currentToken->tokenText << ")\n";
    nextToken();
  } else {
    const auto message = "Unexpected token at '" + currentToken->tokenText;
    abort(message);
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
    abort(message);
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
      expression();
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
    if (labelsDeclared.contains(currentToken->tokenText)) {
      const auto message = std::string("Label already declared: ").append(currentToken->tokenText);
      abort(message);
    }
    labelsDeclared.insert(currentToken->tokenText);
    match(IDENT);
  } else if (checkToken(GOTO)) {
    std::cout << "STATEMENT-GOTO\n";
    nextToken();
    labelsGotoed.insert(currentToken->tokenText);
    match(IDENT);
  } else if (checkToken(LET)) {
    std::cout << "STATEMENT-LET\n";
    nextToken();
    if (!symbols.contains(currentToken->tokenText)) {
      symbols.insert(currentToken->tokenText);
    }
    match(IDENT);
    match(EQ);
    expression();
  } else if (checkToken(INPUT)) {
    std::cout << "STATEMENT-INPUT\n";
    nextToken();
    if (!symbols.contains(currentToken->tokenText)) {
      symbols.insert(currentToken->tokenText);
    }
    match(IDENT);
  } else {
    const auto message = std::string("Invalid statement at ").append(currentToken->tokenText)
    .append(" (").append(toString(currentToken->tokenType)).append(")\n");
    abort(message);
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
