#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "ast/ast.h"
#include "lexer/lexer.h"

typedef std::shared_ptr<Expression>(prefixParseFn)();
typedef std::shared_ptr<Expression>(infixParseFn)(std::shared_ptr<Expression>);

enum class Precedence {
  LOWEST,
  EQUALS,
  LESSGREATER,
  SUM,
  PRODUCT,
  PREFIX,
  CALL,
};

class Parser {
 public:
  Parser(Lexer* l);

  void nextToken();
  bool expectPeek(TokenType t);

  Precedence curPrecedence();
  Precedence peekPrecedence();

  std::shared_ptr<Program> parseProgram();
  std::shared_ptr<Statement> parseStatement();

  std::shared_ptr<Statement> parseLetStatement();
  std::shared_ptr<Statement> parseReturnStatement();
  std::shared_ptr<Statement> parseExpressionStatement();

  std::shared_ptr<Expression> parseExpression(Precedence precedence);
  std::shared_ptr<Expression> parseIdentifier();
  std::shared_ptr<Expression> parseIntegerLiteral();
  std::shared_ptr<Expression> parsePrefixExpression();
  std::shared_ptr<Expression> parseInfixExpression(
      std::shared_ptr<Expression> left);

  void peekError(TokenType t);
  void checkErrors();

  Lexer* l;

  Token curToken;
  Token peekToken;

  std::unordered_map<TokenType, std::function<prefixParseFn>> prefixParseFns;
  std::unordered_map<TokenType, std::function<infixParseFn>> infixParseFns;

  std::vector<std::string> errors;
};