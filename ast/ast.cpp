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
  ss << "(" << op << token.literal << right->String() << ")";
  return ss.str();
}