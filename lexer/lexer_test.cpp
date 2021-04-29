#include "lexer/lexer.h"

#include <gtest/gtest.h>

TEST(NextTokenTest, NextToken) {
  std::string input = "=+(){},;";

  std::vector<Token> tests = {
      // clang-format off
      {ASSIGN, "="},
      {PLUS, "+"},  
      {LPAREN, "("}, 
      {RPAREN, ")"},
      {LBRACE, "{"},
      {RBRACE, "}"}, 
      {COMMA, ","},  
      {SEMICOLON, ";"}, 
      {EOFEND, ""},
      // clang-format on
  };

  Lexer l = Lexer::New(input);

  for (auto& expect_tok : tests) {
    Token tok = l.NextToken();

    EXPECT_STREQ(tok.type.c_str(), expect_tok.type.c_str());
    EXPECT_STREQ(tok.literal.c_str(), expect_tok.literal.c_str());
  }
}