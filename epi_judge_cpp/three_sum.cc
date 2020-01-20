#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasTwoSum(vector<int>& A, int t)
{
  int l = 0, r = A.size() - 1;
  while (l <= r)
  {
    auto res = A[l] + A[r];
    if (res == t)
    {
      return true;
    }
    else if (res < t)
    {
      ++l;
    }
    else
    {
      --r;
    }
  }

  return false;
}

bool HasThreeSum(vector<int> A, int t) {
  std::sort(A.begin(), A.end());

  for (auto& k : A)
  {
    if (HasTwoSum(A, t - k))
    {
      return true;
    }
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
