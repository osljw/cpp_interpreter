
# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "cpp_interpreter",
    srcs = ["main.cpp"],
    copts = [
        "-std=c++2a",
    ],
    deps = [
        "//repl:repl"
    ],
)


