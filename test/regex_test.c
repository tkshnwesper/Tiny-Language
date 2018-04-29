#include "external/unity/src/unity.h"
#include "main/regex.h"

void should_return_null_when_source_is_null() {
  TEST_ASSERT_NULL(match(NULL, ""));
}

void should_return_empty_string_when_source_string_is_empty() {
  TEST_ASSERT_EQUAL_STRING("", match("", "nihao"));
}

void should_return_string_itself_when_pattern_is_equal_to_source() {
  TEST_ASSERT_EQUAL_STRING("hello", match("hello", "hello"));
}

void should_return_partial_match_when_pattern_is_substring_of_source() {
  TEST_ASSERT_EQUAL_STRING("hel", match("hello", "hel"));
}

void should_return_empty_string_when_pattern_is_null() {
  TEST_ASSERT_EQUAL_STRING("", match("hello", NULL));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_return_empty_string_when_source_string_is_empty);
  RUN_TEST(should_return_null_when_source_is_null);
  RUN_TEST(should_return_string_itself_when_pattern_is_equal_to_source);
  RUN_TEST(should_return_partial_match_when_pattern_is_substring_of_source);
  RUN_TEST(should_return_empty_string_when_pattern_is_null);
  return UNITY_END();
}