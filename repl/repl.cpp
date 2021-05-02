#include "repl/repl.h"

#include "lexer/lexer.h"

void Repl::Start() {
  while (true) {
    std::cout << PROMPT;

    std::string input;
    getline(std::cin, input);

    Lexer l(input);

    for (Token tok = l.NextToken(); tok.type != EOFEND; tok = l.NextToken()) {
      std::cout << tok << std::endl;
    }
  }
}