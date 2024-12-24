//
// Created by George Alfaro on 12/17/24.
//
#include <iostream>
#include "lexer.h"
#include "parser.h"

int main() {
  const auto source = "IF+-123 foo*THEN/";
  auto lexer = Lexer(source);
  auto parser = Parser(&lexer);

  auto token = lexer.getToken();
  while (token->tokenType != END_OF_FILE) {
    std::cout << toString(token->tokenType) << std::endl;
    delete token;
    token = lexer.getToken();
  }
  return 0;
}