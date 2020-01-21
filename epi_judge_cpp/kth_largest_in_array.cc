#include <vector>

#include "test_framework/generic_test.h"
#include <random>
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  auto& A = *A_ptr;

  if (A.size() == 0)
  {
    return -1;
  }

  if (k >= A.size())
  {
    return -1;
  }

  std::random_device rd;
  std::default_random_engine gen(rd());

  int l = 0, r = A.size() - 1;
  auto s = k - 1;

  while (l <= r)
  {
    std::uniform_int_distribution<int> dis(l, r);
    auto p = A[dis(gen)];
    auto iter = std::partition(A.begin()+l, A.begin()+r, [&p](const int& a)
      {
        return a > p;
      });

    auto n = iter - A.begin();

    if (n == s)
    {
      return A[n];
    }
    else if (n < s)
    {
      l = n + 1;
    }
    else
    {
      r = n - 1;
    }
  }

  return -1;
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
