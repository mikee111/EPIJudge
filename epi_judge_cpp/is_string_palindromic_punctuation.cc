#include <string>

#include "test_framework/generic_test.h"
#include <locale>
using std::string;

bool IsAlpha(char c)
{
  return std::isalnum(c);
}

void SkipNonAlphas(int& l, int& r, const string& s)
{
  while (l < r && !IsAlpha(s[l]))
    ++l;

	while (l < r && !IsAlpha(s[r]))
		--r;
}

bool IsPalindrome(const string& s) {
  int l = 0;
  int r = s.size() - 1;

  SkipNonAlphas(l, r, s);

  while (l < r)
  {
    if (std::tolower(s[l]) != std::tolower(s[r]))
      return false;

    ++l;
    --r;

    SkipNonAlphas(l, r, s);
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
