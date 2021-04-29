#include "token/token.h"

std::ostream& operator << (std::ostream &os, const Token& tok) { 
    return os << "type=" << tok.type << ", literal=" << tok.literal;
}