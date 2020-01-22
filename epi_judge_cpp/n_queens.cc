#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool CheckPlacement(int col, vector<int>& rowsWithColumn)
{
  auto currentRow = rowsWithColumn.size();
  for (auto row = 0; row < rowsWithColumn.size(); ++row)
  {
    auto diff = std::fabs(col - rowsWithColumn[row]);
    auto diag = diff == (currentRow - row);
    if (diff == 0 || diag)
    {
      return false;
    }
  }

  return true;
}

void NQueensRecurse(int max, vector<int>& rowsWithColumn, vector<vector<int>>& res)
{
  if (rowsWithColumn.size() == max)
  {
    res.push_back(rowsWithColumn);
    return;
  }

  for (auto col = 0; col < max; ++col)
  {
    if (CheckPlacement(col, rowsWithColumn))
    {
			rowsWithColumn.emplace_back(col);
			NQueensRecurse(max, rowsWithColumn, res);
			rowsWithColumn.pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  if (n == 0)
  {
    return {};
  }
  
  vector<vector<int>> res;
  vector<int> c;

  NQueensRecurse(n, c, res);

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
