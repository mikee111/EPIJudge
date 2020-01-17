#include "test_framework/generic_test.h"

unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  // find lowest 1 except the first one
  short pos = 0;
  short val = 0;
  while (!val)
  {
    ++pos;
    val = (x >> pos) & 1;
  }

  // create a zeroing mask
  unsigned long long mask = ~(1LL << pos);

  // and zero it
  x &= mask;

  // create a one mask
  unsigned long long mask2 = 1LL << (pos - 1);

  x |= mask2;

  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
