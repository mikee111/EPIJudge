#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double buy = std::numeric_limits<double>::max();
  double sell = 0;
  double currentProfit = sell - buy;

  for (auto& item : prices)
  {
    if (item < buy)
    {
      buy = item;
    }

    double newProfit = item - buy;
    if (newProfit > currentProfit)
    {
      sell = item;
      currentProfit = newProfit;
    }
  }
  
  return currentProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
