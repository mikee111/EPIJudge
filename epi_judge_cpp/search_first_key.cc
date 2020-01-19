#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  size_t l = 0;
  size_t r = A.size();
  size_t pos = std::numeric_limits<size_t>::max();

  if (A.empty())
  {
    return -1;
  }

  while (true)
  {
    size_t rng = (r - l) / 2;
    size_t m = l + rng;

    if (A[m] == k)
    {
      pos = std::min(m, pos);
      r = m;
    }
    else if (A[m] > k)
    {
      r = m;
    }
    else
    {
      l = m;
    }

    if (rng == 0)
    {
      break;
    }
  }

  return pos;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
