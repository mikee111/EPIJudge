#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int HeightChecker(const unique_ptr<BinaryTreeNode<int>>& tree, int current, bool& failed)
{
  if (failed)
  {
    return -1;
  }

  auto l = tree->left ? HeightChecker(tree->left, current + 1, failed) : current;
  auto r = tree->right ? HeightChecker(tree->right, current + 1, failed) : current;

  if (std::abs(l - r) > 1)
  {
    failed = true;
    return -1;
  }

  return std::max(l,r);
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree)
  {
    return true;
  }

  bool failed = false;

  HeightChecker(tree, 0, failed);

  return !failed;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
