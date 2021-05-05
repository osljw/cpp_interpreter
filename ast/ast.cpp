#include "ast/ast.h"

#include <sstream>
#include <string>

std::string Program::String() {
  std::stringstream ss;

  for (auto& stmt : statements) {
    ss << stmt->String();
  }

  return ss.str();
}

std::string LetStatement::String() {
  std::stringstream ss;
  ss << token.literal << " " << name.String() << " = " << value.String() << ";";
  return ss.str();
}

std::string ReturnStatement::String() {
  std::stringstream ss;
  ss << token.literal << " " << value.String() << ";";
  return ss.str();
}

std::string ExpressionStatement::String() { return expression->String(); }

std::string PrefixExpression::String() {
  std::stringstream ss;
  ss << "(" << op << right->String() << ")";
  return ss.str();
}

std::string InfixExpression::String() {
  std::stringstream ss;
  ss << "(" << left->String() << " " << op << " " << right->String() << ")";
  return ss.str();
}