#include <core/core.hpp>

#include <stdlib.h>
#include <unistd.h>
#include <cstring>

__AFL_FUZZ_INIT();

int main() {
  core::Core core;
#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
#endif

  unsigned char *raw_data = __AFL_FUZZ_TESTCASE_BUF; // get data from mutator

  while (__AFL_LOOP(10000)) {

    int len = __AFL_FUZZ_TESTCASE_LEN;

    if (len == 0) continue; 

    char *input_str = new char[len + 1];
    std::memcpy(input_str, raw_data, len);
    input_str[len] = '\0';

    core.fuzzMeCore(input_str);

    delete[] input_str;
  }
  return 0;
}