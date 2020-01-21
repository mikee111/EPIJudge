#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void Preorder(vector<vector<int>>& res, const unique_ptr<BinaryTreeNode<int>>& tree, int depth)
{
  if (res.size() <= depth)
  {
    res.resize(depth+1);
  }

  res[depth].push_back(tree->data);

  if(tree->left)
    Preorder(res, tree->left, depth + 1);

  if(tree->right)
    Preorder(res, tree->right, depth + 1);
}

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree)
  {
    return {};
  }

  vector<vector<int>> res;
  Preorder(res, tree, 0);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
