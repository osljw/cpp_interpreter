#include "lexer/lexer.h"

#include <iostream>

Lexer& Lexer::New(std::string& input) {
  static Lexer l(input);
  l.readChar();
  return l;
}

void Lexer::readChar() {
  if (readPosition >= input.size()) {
    ch = 0;
  } else {
    ch = input[readPosition];
  }
  position = readPosition;
  readPosition += 1;
}

Token Lexer::NextToken() {
  Token tok;

  std::string literal = std::string(1, ch);

  switch (ch) {
    case '=':
      tok = Token(ASSIGN, literal);
      break;
    case ';':
      tok = Token(SEMICOLON, literal);
      break;
    case '(':
      tok = Token(LPAREN, literal);
      break;
    case ')':
      tok = Token(RPAREN, literal);
      break;
    case '{':
      tok = Token(LBRACE, literal);
      break;
    case '}':
      tok = Token(RBRACE, literal);
      break;
    case ',':
      tok = Token(COMMA, literal);
      break;
    case '+':
      tok = Token(PLUS, literal);
      break;
    case 0:
      tok = Token(EOFEND, literal);
      break;
  }

  readChar();
  return tok;
}