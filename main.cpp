//
// Created by George Alfaro on 12/17/24.
//
#include <iostream>
#include "lexer.h"

int main() {
  auto source = "+- */>>==!=\n";
  auto lexer = Lexer(source);

  auto token = *lexer.getToken();
  while (token.tokenType != END_OF_FILE) {
    std::cout << toString(token.tokenType) << std::endl;
    token = *lexer.getToken();
  }
  return 0;
}