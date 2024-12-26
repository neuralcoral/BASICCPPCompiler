//
// Created by George Alfaro on 12/23/24.
//

#ifndef PARSER_H
#define PARSER_H

#include <unordered_set>

#include "lexer.h"

class Parser {
    std::unordered_set<std::string> symbols;
    std::unordered_set<std::string> labelsDeclared;
    std::unordered_set<std::string> labelsGotoed;
    Lexer * const lexer;
    Token *currentToken;
    Token *peekToken;
    void nextToken();
    static void abort(std::string message);
    [[nodiscard]] bool checkToken(const TokenType& tokenType) const;
    [[nodiscard]] bool checkPeek(const TokenType& tokenType) const;
    void match(const TokenType& tokenType);
    void statement();
    void newline();
    [[nodiscard]] bool isComparisonOperator() const;
    void comparison();
    void expression();
    void term();
    void unary();
    void primary();
  public:
    explicit Parser(Lexer * lexer);
    void program();
};

#endif //PARSER_H
