#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void SpiralBottom(const vector<vector<int>>& m, std::vector<int>& r, int x, int y, int n);

void SpiralTop(const vector<vector<int>>& m, std::vector<int>& r, int x, int y, int n)
{
  // right
  for (int i = 0; i < n; ++i)
  {
    r.push_back(m[x][y + i]);
  }

  // and down
  for (int i = 1; i < n; ++i)
  {
    r.push_back(m[x + i][y + n - 1]);
  }

  --n;
  if(n > 0)
    SpiralBottom(m, r, x + n, y + n - 1, n);
}

void SpiralBottom(const vector<vector<int>>& m, std::vector<int>& r, int x, int y, int n)
{
	// left
	for (int i = 0; i < n; ++i)
	{
		r.push_back(m[x][y - i]);
	}

	// and up
	for (int i = 1; i < n; ++i)
	{
		r.push_back(m[x - i][y - (n - 1)]);
	}

  --n;
  if(n > 0)
    SpiralTop(m, r, x - n, y - n + 1, n);
}

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  std::vector<int> ret;

  if (square_matrix.size() <= 0)
  {
    return {};
  }

  SpiralTop(square_matrix, ret, 0, 0, square_matrix.size());
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
