#pragma once

#include <memory>
#include <vector>

#include "token/token.h"

class Statement {
 public:
  virtual ~Statement() {}
  virtual std::string String() = 0;
};

class Expression {
 public:
  virtual ~Expression(){};
  virtual std::string String() { return "<expression>"; }
};

class Program {
 public:
  std::string String();

  std::vector<std::shared_ptr<Statement>> statements;
};

class Identifier : public Expression {
 public:
  Identifier() {}
  Identifier(Token& token, std::string& value) : token(token), value(value) {}

  std::string tokenLiteral() { return token.literal; }
  std::string String() { return value; }
  Token token;
  std::string value;
};

class IntegerLiteral : public Expression {
 public:
  IntegerLiteral(Token& token, int64_t value) : token(token), value(value) {}
  std::string String() { return std::to_string(value); }

  Token token;
  int64_t value;
};

class PrefixExpression : public Expression {
 public:
  PrefixExpression() {}
  PrefixExpression(Token& token, std::string op,
                   std::shared_ptr<Expression> right)
      : token(token), op(op), right(right) {}
  std::string String();

  Token token;
  std::string op;
  std::shared_ptr<Expression> right;
};

class LetStatement : public Statement {
 public:
  std::string String() override;

  Token token;
  Identifier name;
  Expression value;
};

class ReturnStatement : public Statement {
 public:
  std::string String() override;

  Token token;
  Expression value;
};

class ExpressionStatement : public Statement {
 public:
  std::string String() override;

  Token token;
  std::shared_ptr<Expression> expression;
};
