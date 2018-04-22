cc_test(
  name = "tiny-compiler-tests",
  srcs = glob(["**/*.c"]),
  deps = [
    "//main:Library",
    "@unity",
    "//main:interpret"
  ],
  timeout = "short"
)