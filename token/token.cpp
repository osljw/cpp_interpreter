#include "token/token.h"

std::unordered_map<std::string, std::string> keywords = {
    {"fn", FUNCTION},
    {"let", LET},
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