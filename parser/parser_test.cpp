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

TEST(ParserTest, TestParserProgram) {
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
