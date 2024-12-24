//
// Created by George Alfaro on 12/23/24.
//

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

class Parser {
    const Lexer *lexer;
  public:
    Parser();
    explicit Parser(const Lexer* lexer) : lexer(lexer) {};

};



#endif //PARSER_H
