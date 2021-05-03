#include "parser/parser.h"

void Parser::nextToken() {
  curToken = peekToken;
  peekToken = l->NextToken();
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
  }

  return nullptr;
}

std::shared_ptr<Statement> Parser::parseLetStatement() {
  std::shared_ptr<LetStatement> stmt = std::make_shared<LetStatement>();
  stmt->token = curToken;

  if (!expectPeek(IDENT)) return nullptr;
  stmt->name = Identifier(curToken, curToken.literal);

  if (!expectPeek(ASSIGN)) return nullptr;

  while (curToken.type != SEMICOLON) {
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

bool Parser::expectPeek(TokenType t) {
  if (peekToken.type == t) {
    nextToken();
    return true;
  } else {
    peekError(t);
    return false;
  }
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