#include "token/token.h"

class Lexer {
 public:
  static Lexer& New(std::string& input);

  Lexer(std::string& input) : input(input) {}
  Token NextToken();

  void readChar();
  std::string input;
  int position = 0;
  int readPosition = 0;
  char ch = 0;
};