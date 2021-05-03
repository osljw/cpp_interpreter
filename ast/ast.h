#pragma once

#include <memory>
#include <vector>

#include "token/token.h"

class Statement {
 public:
  virtual ~Statement() {}
};

class Expression {
 public:
};

class Program {
 public:
  std::vector<std::shared_ptr<Statement>> statements;
};

class Identifier {
 public:
  Identifier() {}
  Identifier(Token& token, std::string& value) : token(token), value(value) {}

  std::string tokenLiteral() { return token.literal; }
  Token token;
  std::string value;
};

class LetStatement : public Statement {
 public:
  Token token;
  Identifier name;
  Expression value;
};
