#include "test_framework/generic_test.h"

int SquareRootA(int k) {
  unsigned long long l = 0, r = k;

  if (k == 1)
  {
    return 1;
  }

  while ((r-l)>1)
  {
    unsigned long long m = l + ((r - l) / 2);
    if (m * m <= k)
    {
      l = m;
    }
    else
    {
      r = m;
    }
  }

  return l;
}

int SquareRoot(int k) {
	unsigned long long l = 0, r = k;

	while (l <= r)
	{
		unsigned long long m = l + ((r - l) / 2);
		if (m * m <= k)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}
	}

	return l - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
