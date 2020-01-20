#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindMaximumSubarray(const vector<int>& A) {
  int min, max, sum;
  min = max = sum = 0;

  for (auto i = 0; i < A.size(); ++i)
  {
    sum += A[i];

    if (sum < min)
    {
      min = sum;
    }

    auto loc = sum - min;
    if (loc > max)
    {
      max = loc;
    }
  }

   return max;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "max_sum_subarray.cc", "max_sum_subarray.tsv",
                         &FindMaximumSubarray, DefaultComparator{},
                         param_names);
}
