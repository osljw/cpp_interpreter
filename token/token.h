#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

typedef std::string TokenType;

class Token {
 public:
  Token() {}
  Token(std::string type, std::string literal) : type(type), literal(literal) {}
  Token& operator=(const Token& other) {
    type = other.type;
    literal = other.literal;
    return *this;
  };

  TokenType type;
  std::string literal;
};

std::ostream& operator<<(std::ostream& os, const Token& tok);

const std::string ILLEGAL = "ILLEGAL";
const std::string EOFEND = "EOF";

// Identifiers + literals
const std::string IDENT = "IDENT";  // add, foobar, x, y, ...
const std::string INT = "INT";      // 1343456

// Operators
const std::string ASSIGN = "=";
const std::string PLUS = "+";
const std::string MINUS = "-";
const std::string BANG = "!";
const std::string ASTERISK = "*";
const std::string SLASH = "/";

const std::string LT = "<";
const std::string GT = ">";
const std::string EQ = "==";
const std::string NOT_EQ = "!=";

// Delimiters
const std::string COMMA = ",";
const std::string SEMICOLON = ";";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";

// Keywords
const std::string FUNCTION = "FUNCTION";
const std::string LET = "LET";
const std::string IF = "IF";
const std::string ELSE = "ELSE";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";
const std::string RETURN = "RETURN";

std::string LookupIdent(const std::string& ident);