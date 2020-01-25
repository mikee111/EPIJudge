#include <string>

#include "test_framework/generic_test.h"
using std::string;

int ReadIntFromString(int& pos, const string& expression)
{
  while (expression[pos] != ',' && pos < expression.size())
  {
    ++pos;
  }

  return pos;
}

int DoOperation(int o, int op1, int op2)
{
  switch (o)
  {
  case '+':
    return op1 + op2;
  case '-':
    return op1 - op2;
  case '*':
    return op1 * op2;
  case '/':
    return op1 / op2;    
  }

  assert(false);
  return 0;
}

int Evaluate(const string& expression) {
  std::stack<int> tmp;
  int pos = 0;
  while (pos < expression.size())
  {
    auto start = pos;
    auto end = ReadIntFromString(pos, expression);
    auto len = end - start;

    auto op = expression[start];
    if (len == 1 && op == '+' || op == '-' || op == '*' || op == '/')
    {
			auto op2 = tmp.top();
			tmp.pop();
			auto op1 = tmp.top();
			tmp.pop();
			auto res = DoOperation(op, op1, op2);
			tmp.emplace(res);
    }
    else
    {
      auto sub = expression.substr(start, len);
      auto x = std::atoi(sub.c_str());
      tmp.emplace(x);
    }

    pos = end + 1;
  }

  return tmp.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
