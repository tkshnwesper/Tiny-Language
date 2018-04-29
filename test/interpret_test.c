#include "external/unity/src/unity.h"
#include "main/interpret.h"
#include "main/node.h"

void should_return_nothing_when_blank_input_is_passed() {
  TEST_ASSERT_NULL(interpret(""));
}

void should_return_a_write_token_string_on_write() {
  NODE node = interpret("write \"meow\";");
  TEST_ASSERT_EQUAL_STRING("meow", node->data.node->data.string);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_return_nothing_when_blank_input_is_passed);
  RUN_TEST(should_return_a_write_token_string_on_write);
  return UNITY_END();
}