#include "lexer/lexer.h"

#include <iostream>

// Lexer* Lexer::New(std::string& input) {
//   static Lexer l;
//   l.setInput(input);
//   return &l;
// }

void Lexer::setInput(std::string& input) {
  this->input = input;
  readChar();
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

char Lexer::peekChar() {
  if (readPosition >= input.size()) {
    return 0;
  }

  return input[readPosition];
}

Token Lexer::NextToken() {
  Token tok;

  skipWhitespace();

  std::string literal = std::string(1, ch);
  switch (ch) {
    case '=':
      if (peekChar() == '=') {
        readChar();
        tok = Token(EQ, literal + "=");
      } else {
        tok = Token(ASSIGN, literal);
      }
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
    case '-':
      tok = Token(MINUS, literal);
      break;
    case '*':
      tok = Token(ASTERISK, literal);
      break;
    case '/':
      tok = Token(SLASH, literal);
      break;
    case '<':
      tok = Token(LT, literal);
      break;
    case '>':
      tok = Token(GT, literal);
      break;
    case '!':
      if (peekChar() == '=') {
        readChar();
        tok = Token(NOT_EQ, literal + "=");
      } else {
        tok = Token(BANG, literal);
      }
      break;
    case 0:
      tok = Token(EOFEND, literal);
      break;
    default:
      if (isLetter()) {
        tok.literal = readIdentifier();
        tok.type = LookupIdent(tok.literal);
        return tok;
      } else if (isDigit()) {
        tok = Token(INT, readNumber());
        return tok;
      } else {
        tok = Token(ILLEGAL, literal);
      }
  }

  readChar();
  return tok;
}

void Lexer::skipWhitespace() {
  while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    readChar();
  }
}

bool Lexer::isLetter() {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

std::string Lexer::readIdentifier() {
  int start_pos = position;

  while (isLetter()) {
    readChar();
  }

  return input.substr(start_pos, position - start_pos);
}

bool Lexer::isDigit() { return ('0' <= ch && ch <= '9'); }

std::string Lexer::readNumber() {
  int start_pos = position;
  while (isDigit()) {
    readChar();
  }

  return input.substr(start_pos, position - start_pos);
}