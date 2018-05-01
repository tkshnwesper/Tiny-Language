#include "external/unity/src/unity.h"
#include "main/regex.h"

void should_return_null_when_source_is_null() {
  TEST_ASSERT_NULL(match(NULL, ""));
}

void should_return_null_when_source_string_is_empty() {
  TEST_ASSERT_NULL(match("", "nihao"));
}

void should_return_string_itself_when_pattern_is_equal_to_source() {
  TEST_ASSERT_EQUAL_STRING("hello", match("hello", "hello"));
}

void should_return_partial_match_when_pattern_is_substring_of_source() {
  TEST_ASSERT_EQUAL_STRING("hel", match("hello", "hel"));
}

void should_return_null_when_pattern_is_null() {
  TEST_ASSERT_NULL(match("hello", NULL));
}

void should_return_content_within_parentheses_on_match() {
  TEST_ASSERT_EQUAL_STRING("hel", match("hello", "(hel)"));
}

void should_return_null_when_source_and_pattern_do_not_match() {
  TEST_ASSERT_NULL(match("meow", "hello"));
}

void should_return_null_when_source_and_pattern_do_not_match_with_parentheses() {
  TEST_ASSERT_NULL(match("hello", "(heq)"));
}

void should_return_null_when_match_is_found_in_between_parentheses_but_not_outside() {
  TEST_ASSERT_NULL(match("jello", "h(ell)o"));
}

void should_return_null_when_there_is_mismatch_in_string_after_parentheses() {
  TEST_ASSERT_NULL(match("jello", "je(ll)p"));
}

void should_not_read_a_paren_that_is_part_of_a_string_as_open_paren() {
  TEST_ASSERT_EQUAL_STRING("(meow", match("(meow", "\\(meow"));
}

void should_compare_from_start_when_caret_symbol_is_at_beginning() {
  TEST_ASSERT_EQUAL_STRING("me", match("meow", "^me"));
}

void should_not_match_if_caret_symbol_is_at_start_but_pattern_does_not_match_from_beginning() {
  TEST_ASSERT_NULL(match("meow", "^ow"));
}

void should_compare_from_end_when_dollar_symbol_is_at_end() {
  TEST_ASSERT_EQUAL_STRING("ow", match("meow", "ow$"));
}

void should_not_match_if_dollar_symbol_is_at_end_but_pattern_does_not_match_from_end() {
  TEST_ASSERT_NULL(match("meow", "me$"));
}

void should_not_consider_backslash_as_escape_when_not_preceeding_a_special_character() {
  TEST_ASSERT_EQUAL_STRING("\\me", match("\\meow", "^\\me"));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_return_null_when_source_is_null);
  RUN_TEST(should_return_null_when_source_string_is_empty);
  RUN_TEST(should_return_string_itself_when_pattern_is_equal_to_source);
  RUN_TEST(should_return_partial_match_when_pattern_is_substring_of_source);
  RUN_TEST(should_return_null_when_pattern_is_null);
  RUN_TEST(should_return_content_within_parentheses_on_match);
  RUN_TEST(should_return_null_when_source_and_pattern_do_not_match);
  RUN_TEST(should_return_null_when_source_and_pattern_do_not_match_with_parentheses);
  RUN_TEST(should_return_null_when_match_is_found_in_between_parentheses_but_not_outside);
  RUN_TEST(should_return_null_when_there_is_mismatch_in_string_after_parentheses);
  RUN_TEST(should_not_read_a_paren_that_is_part_of_a_string_as_open_paren);
  RUN_TEST(should_compare_from_start_when_caret_symbol_is_at_beginning);
  RUN_TEST(should_not_match_if_caret_symbol_is_at_start_but_pattern_does_not_match_from_beginning);
  RUN_TEST(should_compare_from_end_when_dollar_symbol_is_at_end);
  RUN_TEST(should_not_match_if_dollar_symbol_is_at_end_but_pattern_does_not_match_from_end);
  RUN_TEST(should_not_consider_backslash_as_escape_when_not_preceeding_a_special_character);
  return UNITY_END();
}
