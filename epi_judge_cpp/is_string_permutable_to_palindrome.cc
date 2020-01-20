#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string& s) {
  
  std::unordered_map<char,unsigned int> ht;

  for (auto& c : s)
  {
    auto i = ht.find(c);
    if (i == ht.end())
    {
      ht.emplace(c, 1);
    }
    else
    {
      ++i->second;
    }
  }

  int odd = 0;
  for (auto iter = ht.begin(); iter != ht.end(); ++iter)
  {
    if (iter->second & 1)
    {
      ++odd;
    }

    if (odd > 1)
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
