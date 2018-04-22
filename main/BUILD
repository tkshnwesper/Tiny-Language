# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "Library",
  srcs = ["Library.c"],
  hdrs = ["Library.h"],
  visibility = ["//test:__pkg__"]
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "Parser",
  srcs = ["Parser.c"],
  hdrs = ["Parser.h"],
  deps = [
    ":Library"
  ],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "Scanner",
  srcs = ["Scanner.c"],
  hdrs = ["Scanner.h"],
  deps = [
    ":Library"
  ],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "interpret",
  srcs = ["interpret.c"],
  hdrs = ["interpret.h"],
  visibility = ["//test:__pkg__"]
)

cc_binary(
  name = "tiny-compiler",
  srcs = ["main.c"],
  deps = [
    ":Library",
    ":Scanner",
    ":Parser"
  ]
)