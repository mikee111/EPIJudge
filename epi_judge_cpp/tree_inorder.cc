#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void Inorder(const unique_ptr<BinaryTreeNode<int>>& tree, vector<int>& data)
{
  if (!tree)
  {
    return;
  }
  
  Inorder(tree->left, data);
  data.push_back(tree->data);
  Inorder(tree->right, data);  
}

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> ret;

  Inorder(tree, ret);

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
