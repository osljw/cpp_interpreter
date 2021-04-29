load("@rules_cc//cc:defs.bzl", "cc_test")




# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.h"],
    deps = [
        "//token:token",
    ],
)

cc_test(
  name = "lexer_test",
  size = "small",
  srcs = ["lexer_test.cpp"],

  deps = [
    ":lexer",
    "@com_google_googletest//:gtest_main",
  ],
)