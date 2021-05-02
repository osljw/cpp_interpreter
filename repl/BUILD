# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "repl",
    srcs = ["repl.cpp"],
    hdrs = ["repl.h"],
    copts = [],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//lexer:lexer",
        "//token:token",
    ],
)