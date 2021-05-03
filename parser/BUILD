load("@rules_cc//cc:defs.bzl", "cc_test")

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//lexer:lexer",
        "//ast:ast",
    ],
)

cc_test(
  name = "parser_test",
  size = "small",
  srcs = ["parser_test.cpp"],
  copts = [
      "-std=c++2a",
  ],
  deps = [
    ":parser",
    "@com_google_googletest//:gtest_main",
  ],
)