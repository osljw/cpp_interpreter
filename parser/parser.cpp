#include "parser/parser.h"

using namespace std::placeholders;

Parser::Parser(Lexer* l) : l(l) {
  nextToken();
  nextToken();

  prefixParseFns[IDENT] = [this]() { return this->parseIdentifier(); };
  prefixParseFns[INT] = [this]() { return this->parseIntegerLiteral(); };
  prefixParseFns[BANG] = [this]() { return this->parsePrefixExpression(); };
  prefixParseFns[MINUS] = [this]() { return this->parsePrefixExpression(); };
}

void Parser::nextToken() {
  curToken = peekToken;
  peekToken = l->NextToken();
}

bool Parser::expectPeek(TokenType t) {
  if (peekToken.type == t) {
    nextToken();
    return true;
  } else {
    peekError(t);
    return false;
  }
}



std::shared_ptr<Program> Parser::parseProgram() {
  std::shared_ptr<Program> program = std::make_shared<Program>();

  while (curToken.type != EOFEND) {
    std::shared_ptr<Statement> stmt = parseStatement();
    if (stmt != nullptr) {
      program->statements.emplace_back(stmt);
    }
    nextToken();
  }

  return program;
}

std::shared_ptr<Statement> Parser::parseStatement() {
  if (curToken.type == LET) {
    return parseLetStatement();
  } else if (curToken.type == RETURN) {
    return parseReturnStatement();
  } else {
    return parseExpressionStatement();
  }

  return nullptr;
}

std::shared_ptr<Statement> Parser::parseLetStatement() {
  std::shared_ptr<LetStatement> stmt = std::make_shared<LetStatement>();
  stmt->token = curToken;

  if (!expectPeek(IDENT)) return nullptr;
  stmt->name = Identifier(curToken, curToken.literal);

  if (!expectPeek(ASSIGN)) return nullptr;

  nextToken();

  if (peekToken.type == SEMICOLON) {
    nextToken();
  }

  return stmt;
}

std::shared_ptr<Statement> Parser::parseReturnStatement() {
  std::shared_ptr<ReturnStatement> stmt = std::make_shared<ReturnStatement>();
  stmt->token = curToken;

  if (!expectPeek(INT)) return nullptr;

  while (curToken.type != SEMICOLON) {
    nextToken();
  }

  return stmt;
}

std::shared_ptr<Statement> Parser::parseExpressionStatement() {
  std::shared_ptr<ExpressionStatement> stmt =
      std::make_shared<ExpressionStatement>();
  stmt->token = curToken;

  stmt->expression = parseExpression(Precedence::LOWEST);

  if (peekToken.type == SEMICOLON) {
    nextToken();
  }

  return stmt;
}


std::shared_ptr<Expression> Parser::parseExpression(Precedence precedence) {
  auto it = prefixParseFns.find(curToken.type);
  if (it == prefixParseFns.end()) {
    std::cerr << "not found prefixParseFn for token: " << curToken << std::endl;
    return nullptr;
  }
  auto prefix = it->second;
  auto left_exp = prefix();

  return left_exp;
}

std::shared_ptr<Expression> Parser::parseIdentifier() {
  std::shared_ptr<Identifier> ident =
      std::make_shared<Identifier>(curToken, curToken.literal);
  return ident;
}

std::shared_ptr<Expression> Parser::parseIntegerLiteral() {
  int64_t value;
  try {
    value = std::stoll(curToken.literal);
  } catch (std::invalid_argument& ex) {
    std::cerr << "stoll invalid argument: " << ex.what() << std::endl;
    return nullptr;
  }
  std::shared_ptr<IntegerLiteral> ident =
      std::make_shared<IntegerLiteral>(curToken, value);
  return ident;
}

std::shared_ptr<Expression> Parser::parsePrefixExpression() {
  std::shared_ptr<PrefixExpression> prefix_exp =
      std::make_shared<PrefixExpression>();
  prefix_exp->token = curToken;
  prefix_exp->op = curToken.literal;

  nextToken();
  prefix_exp->right = parseExpression(Precedence::PREFIX);

  return prefix_exp;
}

void Parser::peekError(TokenType t) {
  std::string msg =
      "expected next token to be " + t + ", got " + peekToken.type + " instead";
  errors.emplace_back(msg);
}

void Parser::checkErrors() {
  if (errors.size() == 0) return;

  std::cerr << "[error] parser has " << errors.size() << " errors" << std::endl;

  for (auto& err : errors) {
    std::cerr << "parser error: " << err << std::endl;
  }
}