#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool Traversal(const unique_ptr<BinaryTreeNode<int>>& tree, int& max)
{
  if (!tree)
  {
    return true;
  }

  if (!Traversal(tree->left, max))
  {
    return false;
  }

  if (tree->data < max)
  {
    return false;
  }

  max = tree->data;

  if (!Traversal(tree->right, max))
  {
      return false;
  }

  return true;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {

  if (!tree)
  {
    return true;
  }

  int max = std::numeric_limits<int>::min();
  return Traversal(tree, max);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
