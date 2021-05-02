#include "token/token.h"

std::unordered_map<std::string, std::string> keywords = {
    // clang-format off
    {"fn", FUNCTION},
    {"let", LET},
    {"if", IF},
    {"else", ELSE},
    {"true", TRUE},
    {"false", FALSE},
    {"return", RETURN},
    // clang-format on
};

std::ostream& operator << (std::ostream &os, const Token& tok) { 
    return os << "type=" << tok.type << ", literal=" << tok.literal;
}

std::string LookupIdent(const std::string& ident) {
  auto it = keywords.find(ident);
  if (it != keywords.end()) {
    return it->second;
  }

  return IDENT;
}