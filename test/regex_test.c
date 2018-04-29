#include "external/unity/src/unity.h"
#include "main/regex.h"

void should_return_empty_string_when_source_string_is_empty() {
  TEST_ASSERT_EQUAL_STRING("", match("", ""));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_return_empty_string_when_source_string_is_empty);
  return UNITY_END();
}