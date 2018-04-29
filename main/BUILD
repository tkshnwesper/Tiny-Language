# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "tokens",
  srcs = ["tokens.c"],
  hdrs = ["tokens.h"],
  # visibility = ["//test:__pkg__"]  
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "node",
  srcs = ["node.c"],
  hdrs = ["node.h"],
  deps = [":tokens"],
  visibility = ["//test:__pkg__"]  
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "keywords",
  srcs = ["keywords.c"],
  hdrs = ["keywords.h"],
  deps = [
    ":node"
  ],
  visibility = ["//test:__pkg__"]  
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "interpret",
  srcs = ["interpret.c"],
  hdrs = ["interpret.h"],
  deps = [
    ":tokens",
    ":node",
    ":keywords"
  ],
  visibility = ["//test:__pkg__"]
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "regex",
  srcs = ["regex.c"],
  hdrs = ["regex.h"],
  visibility = ["//test:__pkg__"]  
)

cc_binary(
  name = "tiny-compiler",
  srcs = ["main.c"],
  deps = []
)