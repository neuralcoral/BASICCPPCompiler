//
// Created by George Alfaro on 12/18/24.
//

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H
#include <unordered_map>

enum TokenType {
  END_OF_FILE = -1,
  NEWLINE = 0,
  NUMBER = 1,
  IDENT = 2,
  STRING = 3,
  LABEL = 101,
  GOTO = 102,
  PRINT = 103,
  INPUT = 104,
  LET = 105,
  IF = 106,
  THEN = 107,
  ENDIF = 108,
  WHILE = 109,
  REPEAT = 110,
  ENDWHILE = 111,
  EQ = 201,
  PLUS = 202,
  MINUS = 203,
  ASTERISK = 204,
  SLASH = 205,
  EQEQ = 206,
  NOTEQ = 207,
  LT = 208,
  LTEQ = 209,
  GT = 210,
  GTEQ = 211
};

std::string toString(const TokenType& tokenType);


#endif //TOKEN_TYPE_H
