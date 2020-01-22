#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
const int kMPG = 20;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
int FindAmpleCity(const vector<int>& gallons, const vector<int>& distances) {
  struct {
    int id = 0;
    int gas = 0;
  } bestCity;

  int gas = 0;
	for (auto i = 1; i < gallons.size(); ++i)
	{
		gas += gallons[i - 1] * kMPG - distances[i - 1];
    if (gas < bestCity.gas)
    {
      bestCity = { i,gas };
    }
	}

  return bestCity.id;
}

int FindAmpleCityN2(const vector<int>& gallons, const vector<int>& distances) {

  vector<int> sum(gallons.size(),0);

  for (auto i = 0; i < gallons.size(); ++i)
  {
    for (auto j = 0; j < gallons.size(); ++j)
    {
      if (sum[j] < 0)
        continue;

      auto k = (j + i) % gallons.size();
      sum[j] += gallons[k] * kMPG - distances[k];
    }
  }

  for (auto i = 0; i < sum.size(); ++i)
  {
    if (sum[i] == 0)
    {
      return i;
    }
  }

  return -1;
}

void FindAmpleCityWrapper(TimedExecutor& executor, const vector<int>& gallons,
                          const vector<int>& distances) {
  int result = executor.Run([&] { return FindAmpleCity(gallons, distances); });
  const int num_cities = gallons.size();
  int tank = 0;
  for (int i = 0; i < num_cities; ++i) {
    int city = (result + i) % num_cities;
    tank += gallons[city] * kMPG - distances[city];
    if (tank < 0) {
      throw TestFailure(FmtStr("Out of gas on city {}", i));
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "gallons", "distances"};
  return GenericTestMain(args, "refueling_schedule.cc",
                         "refueling_schedule.tsv", &FindAmpleCityWrapper,
                         DefaultComparator{}, param_names);
}
