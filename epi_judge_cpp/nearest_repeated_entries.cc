#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include <unordered_map>
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
  
  std::unordered_map <string, std::vector<int>> c;

  int i = 0;
  for (auto& str : paragraph)
  {
    c.emplace(str, i);
    ++i;
  }

  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
