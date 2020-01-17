#include "test_framework/generic_test.h"

const auto cacheSize = 0xffff;
const auto bitSize = 16;
std::array<bool, cacheSize + 1> cacheData;

short ComputeParity(int x)
{
  short result = 0;
	while (x)
	{
		result ^= 1;
		x &= (x - 1);
	}

	return result;
}

int GetPart(unsigned long long x, unsigned char num)
{
	return (x >> bitSize * num) & cacheSize;
}

short GetParity(unsigned long long x)
{
	auto a = cacheData[GetPart(x, 3)];
	auto b = cacheData[GetPart(x, 2)];
	auto c = cacheData[GetPart(x, 1)];
	auto d = cacheData[GetPart(x, 0)];
	return a ^ b ^ c ^ d;
}

short Parity(unsigned long long x) {
	return GetParity(x);
}

int main(int argc, char* argv[]) {
	int pos = 0;
	for (auto& data : cacheData)
	{
		data = ComputeParity(pos);
		++pos;
	}

  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
