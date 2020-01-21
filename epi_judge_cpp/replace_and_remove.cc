#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  auto sz = size;
  auto curr = 0;
  int aShift = 0;

  for(int i = 0; i < size; ++i)
  {
    auto& c = s[i];

    if (c == 'a')
    {
      ++aShift;
      s[curr++] = c;
    }
    else if (c == 'b')
    {

      --sz;
    }
    else
    {
      s[curr++] = c;
    }
  }

  auto total = curr + aShift;
  auto backPos = total - 1;
  --curr;

  while (curr >= 0)
  {
    auto c = s[curr--];
    if (c == 'a')
    {
      s[backPos--] = 'd';
      s[backPos--] = 'd';
    }
    else
    {
      s[backPos--] = c;
    }
  }

  return total;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
