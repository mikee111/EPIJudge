#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include <unordered_map>
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
  
  // name -> (last_occurence)
  std::unordered_map <string, int> c;
  int minlen = std::numeric_limits<int>::max();

  int i = 0;
  for (auto& str : paragraph)
  {
    auto iter = c.find(str);
    if (iter != c.end())
    {
      int len = i - iter->second;
      minlen = std::min(len, minlen);
      iter->second = i;
    }
    else
    {
      c.emplace(str, i);
    }
    
    ++i;
  }

  return minlen == std::numeric_limits<int>::max() ? -1 : minlen;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
