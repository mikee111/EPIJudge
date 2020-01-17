#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kRed, kWhite, kBlue };

void DutchFlagPartition_Lame(int pivot_index, vector<Color>* A_ptr) {
  
  std::array<int, 3> num;
  std::fill(num.begin(), num.end(), 0);

  auto& A = *A_ptr;
  for (auto& item : A)
  {
    ++num[static_cast<int>(item)];
  }

  int color = 0;
  int pos = 0;
  for (auto& item : num)
  {
    for (unsigned int i = 0; i < item; ++i,++pos)
    {
      A[pos] = static_cast<Color>(color);
    }

    ++color;
  }

  return;
}

static int test = 0;

void DutchFlagPartition_STL(int pivot_index, vector<Color>* A_ptr) {
  auto& A = *A_ptr;

  if (A.size() <= 1)
  {
    return;
  }

  Color p = A[pivot_index];

  auto b = std::partition(A.begin(), A.end(), [&p](const Color& a) {
    return a <= p;
    });

	std::partition(A.begin(), b, [&p](const Color& a) {
		return a < p;
		});

	return;
}

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
	auto& A = *A_ptr;

  // todo manual

	return;
}


void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
