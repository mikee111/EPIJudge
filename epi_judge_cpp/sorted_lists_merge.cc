#include "list_node.h"
#include "test_framework/generic_test.h"

typedef shared_ptr<ListNode<int>> ListPtr;

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  ListPtr head(new ListNode<int>);
  ListPtr curr = head;

  while (L1 && L2)
  {
    ListPtr& act = L1->data < L2->data ? L1 : L2;
    curr->next = act;
    curr = act;

    act = act->next;
  }

  if (L1)
  {
    curr->next = L1;
  }
  else
  {
    curr->next = L2;
  }

  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
