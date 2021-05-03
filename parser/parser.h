#pragma once

#include <memory>

#include "ast/ast.h"
#include "lexer/lexer.h"

class Parser {
 public:
  Parser(Lexer* l) : l(l) {
    nextToken();
    nextToken();
  }

  void nextToken();
  bool expectPeek(TokenType t);

  std::shared_ptr<Program> parseProgram();
  std::shared_ptr<Statement> parseStatement();

  std::shared_ptr<Statement> parseLetStatement();
  std::shared_ptr<Statement> parseReturnStatement();

  void peekError(TokenType t);
  void checkErrors();

  Lexer* l;

  Token curToken;
  Token peekToken;

  std::vector<std::string> errors;
};