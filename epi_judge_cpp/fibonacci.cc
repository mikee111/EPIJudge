#include "test_framework/generic_test.h"
int Fibonacci(int n) {

  if (n <= 0)
  {
    return 0;
  }
  else if (n == 1)
  {
    return 1;
  }

  int prev = 0;
  int curr = 1;

  for (auto i = 2; i <= n; ++i)
  {
    int tmp = curr;
    curr = curr + prev;
    prev = tmp;
  }

  return curr;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
