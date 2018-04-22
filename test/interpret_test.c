#include "external/unity/src/unity.h"
#include "main/interpret.h"

void should_return_nothing_when_blank_input_is_passed() {
  TEST_ASSERT_NULL(interpret(""));
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(should_return_nothing_when_blank_input_is_passed);
  return UNITY_END();
}