#include <string>

#include "test_framework/generic_test.h"
using std::string;

char FormDigit(int d)
{
  if (d < 10)
  {
    return '0' + d;
  }
  else if (d >= 10 && d < 16)
  {
    return 'A' + d - 10;
  }

  assert(false);
  return 'X';
}

int GetDigit(char c)
{
  if (c >= '0' && c <= '9')
  {
    return c - '0';
  }
  else if (c >= 'A' && c <= 'F')
  {
    return c - 'A' + 10;
  }

  assert(false);
  return 'X';
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  if (num_as_string.size() == 0)
  {
    return "";
  }
  
  char s = 0;
  auto e = num_as_string.begin();
  if (num_as_string[0] == '-' || num_as_string[0]=='+')
  {
    ++e;
    s = num_as_string[0];
  }

  // get b1 to decimal
  int dec = 0;
  int mult = 1;
  auto c = num_as_string.end();
  do
  {
    --c;
    int d = GetDigit(*c);
    dec += d * mult;
    mult *= b1;
  } while (c != e);

  // form b2 from decimal
  string ret;
  do
  {
    int p = dec % b2;
    char r = FormDigit(p);

    ret.push_back(r);

    dec -= p;
    dec /= b2;
  } while (dec != 0);

  if (s != 0)
  {
    ret.push_back(s);
  }
  
  std::reverse(ret.begin(), ret.end());

  return ret;

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
