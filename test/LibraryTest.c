#include "external/unity/src/unity.h"

void sample_test() {
  TEST_ASSERT(1 == 1);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(sample_test);
  UNITY_END();
  return 0;
}