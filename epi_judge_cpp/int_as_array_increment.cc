#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  for (auto i = A.rbegin(); i != A.rend(); ++i)
  {
    if (*i == 9)
    {
      *i = 0;
    }
    else
    {
      ++(*i);
      return A;
    }
  }

  A.insert(A.begin(), 1);

  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
