#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

using TCache = vector<vector<int>>;

int ComputeDistance(TCache& cache, const string& A, int a, const string& B, int b)
{
  if (a < 0 || b < 0)
  {
    return std::abs(a - b);
  }

  if (cache[a][b] == -1)
  {
    if (A[a] == B[b])
    {
      int ret = ComputeDistance(cache, A, a - 1, B, b - 1);
      cache[a][b] = ret;
    }
    else
    {
			// insert, A, B-1
      int ins = ComputeDistance(cache, A, a, B, b - 1);
		  // delete, A-1, B
      int del = ComputeDistance(cache, A, a-1, B, b);
		  // substitute, A-1, A-1
      int sub = ComputeDistance(cache, A, a-1, B, b - 1);
      int ret = 1 + std::min(ins, std::min(del, sub));
      cache[a][b] = ret;
    }
  }

  return cache[a][b];
}

int LevenshteinDistance(const string& A, const string& B) {
  
  TCache dist(A.size(), vector<int>(B.size(), -1));

  return ComputeDistance(dist,A,A.size()-1,B,B.size()-1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
