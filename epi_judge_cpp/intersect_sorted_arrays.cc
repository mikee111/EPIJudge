#include <vector>
#include <set>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  std::vector<int> ret;

  size_t posA = 0, posB = 0;

  while (posA < A.size() && posB < B.size())
  {
    auto& a = A[posA];
    auto& b = B[posB];

    if (posA != 0 && a == A[posA - 1])
    {
      ++posA;
      continue;
    }

    if (a == b)
    {
      ret.emplace_back(a);
      ++posA;
      ++posB;
    }
    else if(a < b)
    {
      ++posA;
    }
    else
    {
      ++posB;
    }
  }

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
