#include "lexer/lexer.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(NextTokenTest, NextTokenSimple) {
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

  Lexer l(input);

  for (auto& expect_tok : tests) {
    Token tok = l.NextToken();

    EXPECT_STREQ(tok.type.c_str(), expect_tok.type.c_str());
    EXPECT_STREQ(tok.literal.c_str(), expect_tok.literal.c_str());
  }
}

TEST(NextTokenTest2, NextTokenT2) {
  std::string input = R"code(
    let five = 5;
    let ten = 10;

    let add = fn(x, y) {
        x + y;
    };

    let result = add(five, ten);

    !-/*5
    <>return,true
  )code";

  std::cout << "input:" << input << std::endl;

  std::vector<Token> tests = {
      // clang-format off
      {LET, "let"},
      {IDENT, "five"},
      {ASSIGN, "="},
      {INT, "5"},
      {SEMICOLON, ";"},

      {LET, "let"},
      {IDENT, "ten"},
      {ASSIGN, "="},
      {INT, "10"},
      {SEMICOLON, ";"},

      {LET, "let"},
      {IDENT, "add"},
      {ASSIGN, "="},
      {FUNCTION, "fn"},
      {LPAREN, "("},
      {IDENT,"x"},
      {COMMA,","},
      {IDENT,"y"},
      {RPAREN,")"},
      {LBRACE,"{"},
      {IDENT,"x"},
      {PLUS,"+"},
      {IDENT,"y"},
      {SEMICOLON,";"},
      {RBRACE,"}"},
      {SEMICOLON,";"},

      {LET,"let"},
      {IDENT,"result"},
      {ASSIGN,"="},
      {IDENT,"add"},
      {LPAREN,"("},
      {IDENT,"five"},
      {COMMA,","},
      {IDENT,"ten"},
      {RPAREN,")"},
      {SEMICOLON,";"},

      {BANG, "!"},
      {MINUS, "-"},
      {SLASH, "/"},
      {ASTERISK, "*"},
      {INT, "5"},
      {LT, "<"},
      {GT, ">"},
      {RETURN, "return"},
      {COMMA, ","},
      {TRUE, "true"},

      {EOFEND, ""},
      // clang-format on
  };

  Lexer l(input);

  for (auto& expect_tok : tests) {
    Token tok = l.NextToken();

    EXPECT_STREQ(tok.type.c_str(), expect_tok.type.c_str());
    EXPECT_STREQ(tok.literal.c_str(), expect_tok.literal.c_str());
  }
}