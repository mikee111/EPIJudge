#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArraysSlower(vector<int>& A, int m, const vector<int>& B, int n) {
  int c = m + n - 1;
  --m;
  --n;
  for (int i = c; i >= 0; i--)
  {
    if (n < 0)
    {
      A[i] = A[m--];
    }
    else if (m < 0)
    {
      A[i] = B[n--];
    }
    else if (A[m] > B[n])
    {
      A[i] = A[m--];
    }
    else
    {
      A[i] = B[n--];
    }
  }

  return;
}

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  int i = m + n - 1;
  --m; --n;
	for (; i >= 0; i--)
	{
		if (m < 0 || n < 0)
		{
			break;
		}

		if (A[m] > B[n])
		{
			A[i] = A[m--];
		}
		else
		{
			A[i] = B[n--];
		}
	}

  bool Bout = n < 0;
  int& j = Bout ? m : n;
  const vector<int>& C = Bout ? A : B;

  for (; i >= 0; i--)
  {
    A[i] = C[j--];
  }

	return;
}

vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
