//
// Created by George Alfaro on 12/18/24.
//
#include "token_type.h"
const char* toString(const TokenType& tokenType) {
  switch (tokenType) {
    case TokenType::END_OF_FILE: return "END_OF_FILE";
    case TokenType::NEWLINE: return "NEWLINE";
    case TokenType::NUMBER: return "NUMBER";
    case TokenType::IDENT: return "IDENT";
    case TokenType::STRING: return "STRING";
    case TokenType::LABEL: return "LABEL";
    case TokenType::GOTO: return "GOTO";
    case TokenType::PRINT: return "PRINT";
    case TokenType::INPUT: return "INPUT";
    case TokenType::LET: return "LET";
    case TokenType::IF: return "IF";
    case TokenType::THEN: return "THEN";
    case TokenType::ENDIF: return "ENDIF";
    case TokenType::WHILE: return "WHILE";
    case TokenType::REPEAT: return "REPEAT";
    case TokenType::ENDWHILE: return "ENDWHILE";
    case TokenType::EQ: return "EQ";
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::ASTERISK: return "ASTERISK";
    case TokenType::SLASH: return "SLASH";
    case TokenType::EQEQ: return "EQEQ";
    case TokenType::NOTEQ: return "NOTEQ";
    case TokenType::LT: return "LT";
    case TokenType::LTEQ: return "LTEQ";
    case TokenType::GT: return "GT";
    case TokenType::GTEQ: return "GTEQ";
    default: return "UNKNOWN";
  }
};