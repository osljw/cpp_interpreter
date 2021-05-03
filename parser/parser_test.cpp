#include "parser/parser.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

bool testLetStatement(std::shared_ptr<Statement> stmt, std::string& name) {
  std::shared_ptr<LetStatement> let_stmt =
      std::dynamic_pointer_cast<LetStatement>(stmt);
  if (let_stmt == nullptr) {
    std::cerr << "dynamic pointer cast to LetStatement error!" << std::endl;
    return false;
  }
  if (let_stmt->token.literal != "let") {
    std::cerr << name << " is not let statement" << std::endl;
    return false;
  }

  if (let_stmt->name.value != name) return false;
  if (let_stmt->name.tokenLiteral() != name) return false;
  return true;
}

TEST(ParserTest, TestLetStatements) {
  std::string input = R"code(
    let x = 5;
    let y = 10;
    let foobar = 838383;
  )code";

  Lexer l(input);
  Parser p(&l);

  std::shared_ptr<Program> program = p.parseProgram();
  p.checkErrors();
  EXPECT_NE(program, nullptr);
  EXPECT_EQ(program->statements.size(), 3);

  std::vector<std::string> test = {
      {"x"},
      {"y"},
      {"foobar"},
  };

  for (uint i = 0; i < test.size(); i++) {
    std::shared_ptr<Statement> stmt = program->statements[i];
    EXPECT_TRUE(testLetStatement(stmt, test[i]));
  }
}


bool testReturnStatement(std::shared_ptr<Statement>& stmt, std::string& value) {
  std::shared_ptr<ReturnStatement> return_statement =
      std::dynamic_pointer_cast<ReturnStatement>(stmt);

  if (return_statement == nullptr) {
    std::cerr << "dynamic pointer cast to ReturnStatement error" << std::endl;
    return false;
  }

  return true;
}

TEST(ParserTest, TestReturnStatements) {
  std::string input = R"code(
    return 5;
    return 10;
    return 993322;
  )code";

  Lexer l(input);
  Parser p(&l);

  std::shared_ptr<Program> program = p.parseProgram();
  p.checkErrors();
  EXPECT_NE(program, nullptr);
  EXPECT_EQ(program->statements.size(), 3);

  std::vector<std::string> test = {
      {"5"},
      {"10"},
      {"993322"},
  };

  for (uint i = 0; i < test.size(); i++) {
    std::shared_ptr<Statement> stmt = program->statements[i];
    EXPECT_TRUE(testReturnStatement(stmt, test[i]));
  }
}

TEST(ParserTest, TestIdentifierExpression) {
  std::string input = "foobar";

  Lexer l(input);
  Parser p(&l);

  std::shared_ptr<Program> program = p.parseProgram();
  p.checkErrors();

  EXPECT_EQ(program->statements.size(), 1);
  std::shared_ptr<Statement> stmt = program->statements[0];
  std::shared_ptr<ExpressionStatement> expression_stmt =
      std::dynamic_pointer_cast<ExpressionStatement>(stmt);

  EXPECT_NE(expression_stmt, nullptr);
  EXPECT_TRUE(expression_stmt->token.type == IDENT);
  EXPECT_TRUE(expression_stmt->token.literal == "foobar");
}

TEST(ParserTest, TestIntegerExpression) {
  std::string input = "555";

  Lexer l(input);
  Parser p(&l);

  std::shared_ptr<Program> program = p.parseProgram();
  p.checkErrors();

  EXPECT_EQ(program->statements.size(), 1);
  std::shared_ptr<Statement> stmt = program->statements[0];
  std::shared_ptr<ExpressionStatement> expression_stmt =
      std::dynamic_pointer_cast<ExpressionStatement>(stmt);

  EXPECT_NE(expression_stmt, nullptr);
  EXPECT_TRUE(expression_stmt->token.type == INT);
  EXPECT_TRUE(expression_stmt->token.literal == "555");

  std::shared_ptr<IntegerLiteral> integer_literal =
      std::dynamic_pointer_cast<IntegerLiteral>(expression_stmt->expression);
  EXPECT_NE(integer_literal, nullptr);
  EXPECT_TRUE(integer_literal->value == 555);
}

class PrefixCase {
 public:
  PrefixCase(std::string input, std::string op, int64_t integer_value)
      : input(input), op(op), integer_value(integer_value) {}
  std::string input;
  std::string op;
  int64_t integer_value;
};

TEST(ParserTest, TestPrefixExpression) {
  std::vector<PrefixCase> tests = {
      {"!5", "!", 5},
      {"-15", "-", 15},
  };

  for (auto& tt : tests) {
    Lexer l(tt.input);
    Parser p(&l);

    std::shared_ptr<Program> program = p.parseProgram();
    p.checkErrors();

    EXPECT_EQ(program->statements.size(), 1);

    std::shared_ptr<ExpressionStatement> expression_stmt =
        std::dynamic_pointer_cast<ExpressionStatement>(program->statements[0]);
    EXPECT_NE(expression_stmt, nullptr);
    EXPECT_TRUE(expression_stmt->token.type == tt.op);

    std::shared_ptr<PrefixExpression> prefix_exp =
        std::dynamic_pointer_cast<PrefixExpression>(
            expression_stmt->expression);
    EXPECT_NE(prefix_exp, nullptr);
    EXPECT_TRUE(prefix_exp->op == tt.op);

    EXPECT_NE(prefix_exp->right, nullptr);
    std::cout << "prefix right: " << prefix_exp->right->String() << std::endl;
  }
}