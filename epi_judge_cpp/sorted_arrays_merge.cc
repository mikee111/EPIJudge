#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct Item
{
  int val;
  int pos;
  const vector<int>* arr;

  Item(int v, int p, const vector<int>* a) :val(v), pos(p), arr(a)
  {

  }
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  auto Comp = [](const Item& a, const Item& b) -> bool
  {
    return a.val > b.val;
  };

  std::priority_queue<Item, std::vector<Item>, decltype(Comp)> q(Comp);

  for (auto& arr : sorted_arrays)
  {
    q.emplace(arr[0],0,&arr);
  }

  vector<int> res;

  while (!q.empty())
  {
    auto t = q.top();
    q.pop();

    res.push_back(t.val);

    ++t.pos;
    if (t.pos < t.arr->size())
    {
      t.val = t.arr->at(t.pos);
      q.emplace(t);
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
