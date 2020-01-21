#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int ComputeDepth(const unique_ptr<BinaryTreeNode<int>>& node)
{
  auto* p = node.get();
  int depth = 0;
  while (p->parent)
  {
    ++depth;
    p = p->parent;
  }
  return depth;
}

BinaryTreeNode<int>* Advance(BinaryTreeNode<int>* p, int depth)
{
  for (auto i = 0; i < depth; ++i)
  {
    p = p->parent;
  }

  return p;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  auto d0 = ComputeDepth(node0);
  auto d1 = ComputeDepth(node1);
  auto m = std::max(d0, d1);

  auto* p0 = node0.get();
  auto* p1 = node1.get();

  if (d0 > d1)
  {
    p0 = Advance(p0, d0 - d1);
  }
  else if (d1 > d0)
  {
    p1 = Advance(p1, d1 - d0);
  }

  while (p0 != p1)
  {
    p0 = Advance(p0, 1);
    p1 = Advance(p1, 1);
  }

  return p0;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
