#include <iostream>
#include <string>

#include "repl/repl.h"

int main() {
  std::string username = "sir";
  std::cout << "Hello " << username
            << "! This is the Monkey programming language!" << std::endl;
  std::cout << "Feel free to type in commands" << std::endl;

  Repl repl;
  repl.Start();

  return 0;
}