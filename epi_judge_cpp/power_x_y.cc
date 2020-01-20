#include "test_framework/generic_test.h"
double Power(double x, int y) {
  auto res = 1.0;
  auto mult = x;
  auto ex = std::abs(y);
  
  while (ex)
  {
    // active mult?
    int act = ex & 1;

    if (act)
    {
      res *= mult;
    }

    mult *= mult;

    // remove active
    ex >>= 1;
  }

  return y < 0 ? 1.0 / res : res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
