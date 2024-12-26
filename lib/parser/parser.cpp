//
// Created by George Alfaro on 12/23/24.
//

#include "parser.h"

#include <iostream>

class Emitter;

Parser::Parser(Lexer * lexer, Emitter * emitter) : lexer(lexer), emitter(emitter) {
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
  emitter->headerLine("#include <stdio.h>");
  emitter->headerLine("int main(void) {");
  while (checkToken(NEWLINE)) {
    nextToken();
  }

  while (!checkToken(TokenType::END_OF_FILE)) {
    statement();
  }

  emitter->emitLine("return 0;");
  emitter->emitLine("}");

  for (const auto& label : labelsGotoed) {
    if (!labelsDeclared.contains(label)) {
      const auto message = std::string("Attempting to GOTO to undeclared label: '").append(label).append("'.\n");
      abort(message);
    }
  }
}

void Parser::expression() {
  term();
  while (checkToken(PLUS) || checkToken(MINUS)) {
    emitter->emit(currentToken->tokenText);
    nextToken();
    term();
  }
}

void Parser::term() {
  unary();
  while (checkToken(ASTERISK) || checkToken(SLASH)) {
    emitter->emit(currentToken->tokenText);
    nextToken();
    unary();
  }
}

void Parser::unary() {
  if (checkToken(PLUS) || checkToken(MINUS)) {
    emitter->emit(currentToken->tokenText);
    nextToken();
  }
  primary();
}

void Parser::primary() {
  if (checkToken(NUMBER)) {
    emitter->emit(currentToken->tokenText);
    nextToken();
  } else if (checkToken(IDENT)) {
    if (!symbols.contains(currentToken->tokenText)) {
      abort("Referencing variable before assignment: " + currentToken->tokenText);
    }
    emitter->emit(currentToken->tokenText);
    nextToken();
  } else {
    abort("Unexpected token at '" + currentToken->tokenText);
  }
}


void Parser::comparison() {
  expression();
  if (isComparisonOperator()) {
    emitter->emit(currentToken->tokenText);
    nextToken();
    expression();
  } else {
    abort("Expected comparison operator at: '" + currentToken->tokenText);
  }

  while (isComparisonOperator()) {
    emitter->emit(currentToken->tokenText);
    nextToken();
    expression();
  }
}

bool Parser::isComparisonOperator() const {
  return checkToken(EQEQ) || checkToken(NOTEQ) || checkToken(GT) || checkToken(GTEQ) || checkToken(LT) || checkToken(LTEQ);
}


void Parser::statement() {
  if (checkToken(PRINT)) {
    nextToken();

    if (checkToken(TokenType::STRING)) {
      emitter->emitLine("printf(\"" + currentToken->tokenText + "\\n\");");
      nextToken();
    } else {
      emitter->emit(R"(printf("%.2f\n", (float)()");
      expression();
      emitter->emitLine("));");
    }
  } else if (checkToken(TokenType::IF)) {
    nextToken();
    emitter->emit("if(");
    comparison();

    match(THEN);
    newline();
    emitter->emitLine("){");

    while (!checkToken(ENDIF)) {
      statement();
    }

    match(ENDIF);
    emitter->emitLine("}");

  } else if (checkToken(TokenType::WHILE)) {
    nextToken();
    emitter->emit("while(");
    comparison();

    match(REPEAT);
    newline();
    emitter->emitLine("){");

    while (!checkToken(ENDWHILE)) {
      statement();
    }

    match(ENDWHILE);
    emitter->emitLine("}");
  } else if (checkToken(LABEL)) {
    nextToken();

    if (labelsDeclared.contains(currentToken->tokenText)) {
      const auto message = std::string("Label already declared: ").append(currentToken->tokenText);
      abort(message);
    }
    labelsDeclared.insert(currentToken->tokenText);

    emitter->emitLine(currentToken->tokenText + ":");
    match(IDENT);
  } else if (checkToken(GOTO)) {
    nextToken();
    labelsGotoed.insert(currentToken->tokenText);
    emitter->emitLine("goto " + currentToken->tokenText + ";");
    match(IDENT);
  } else if (checkToken(LET)) {
    nextToken();

    if (!symbols.contains(currentToken->tokenText)) {
      symbols.insert(currentToken->tokenText);
      emitter->headerLine("float " + currentToken->tokenText + ";");
    }

    emitter->emit(currentToken->tokenText + " = ");
    match(IDENT);
    match(EQ);

    expression();
    emitter->emitLine(";");
  } else if (checkToken(INPUT)) {
    std::cout << "STATEMENT-INPUT\n";
    nextToken();
    if (!symbols.contains(currentToken->tokenText)) {
      symbols.insert(currentToken->tokenText);
      emitter->headerLine("float " + currentToken->tokenText + ";");
    }
    emitter->emitLine("if(0 == scanf(\"%f\", &" + currentToken->tokenText + ")) {");
    emitter->emitLine(currentToken->tokenText + " = 0;");
    emitter->emitLine("scanf(\"%*s\");");
    emitter->emitLine("}");
    match(IDENT);
  } else {
    const auto message = std::string("Invalid statement at ").append(currentToken->tokenText)
    .append(" (").append(toString(currentToken->tokenType)).append(")\n");
    abort(message);
  }
  newline();
}

void Parser::newline() {
  match(TokenType::NEWLINE);
  while (checkToken(TokenType::NEWLINE)) {
    nextToken();
  }
}
