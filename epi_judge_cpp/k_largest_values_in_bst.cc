#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void RevInOrder(BstNode<int>* node, vector<int>& res, int k)
{
  if (node->right)
    RevInOrder(node->right.get(),res,k);

  if (res.size() < k)
  {
    res.push_back(node->data);
  }

  if (node->left)
    RevInOrder(node->left.get(),res,k);
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  
  vector<int> res;
  RevInOrder(tree.get(), res, k);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
