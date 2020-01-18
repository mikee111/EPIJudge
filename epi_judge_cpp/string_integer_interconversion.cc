#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  long long nx = x;

  string str = "";
  if (nx < 0)
	{
		str += '-';
		nx = std::abs(nx);
	}

  int len = log10(nx);  

  for (auto i = len; i > 0; --i)
  {
    int divisor = std::pow(10, i);
    int part = nx / divisor;
    nx -= divisor * part;
    str += ('0' + part);
  }

  str += ('0' + nx);

  return str.c_str();
}
int StringToInt(const string& s) {
  string ns = s;

  auto len = ns.size() - 1;
  int ret = 0;

  auto i = 0;
  bool invert = false;

  if (ns[0] == '+')
  {
    ++i;
    --len;
  }
  else if (ns[0] == '-')
  {
    ++i;
    --len;
    invert = true;
  }

  for (;i<ns.size();++i)
  {
    auto n = ns[i] - '0';
    auto pos = pow(10, len--);
    ret += pos * n;
  }

  if (invert)
  {
    ret *= -1;
  }

  return ret;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}