#include "token/token.h"

class Lexer {
 public:
  // static Lexer* New(std::string& input);

  Lexer(std::string input) : input(input) { readChar(); };
  void setInput(std::string& input);
  Token NextToken();

  void skipWhitespace();
  void readChar();
  char peekChar();

  bool isLetter();
  std::string readIdentifier();

  bool isDigit();
  std::string readNumber();

  std::string input;
  int position = 0;
  int readPosition = 0;
  char ch = 0;
};