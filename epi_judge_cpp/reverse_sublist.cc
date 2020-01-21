#include "list_node.h"
#include "test_framework/generic_test.h"

using TNode = shared_ptr<ListNode<int>>;

void SubReverse(TNode s, TNode f)
{
  TNode p = s;
  TNode c = s->next;

  do
  {
    auto tmp = c->next;
    c->next = p;

    p = c;
    c = tmp;
  } while (p != f);
}

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {

	if (start == finish)
	{
		return L;
	}

  int pos = 1;
  TNode curr, prev;
  TNode s, f, p, a;
  curr = L;  

  while (curr && pos <= finish)
  {
    if (pos == start)
    {
      s = curr;
      p = prev;
    }
    else if (pos == finish)
    {
      f = curr;
      a = curr->next;
    }

    prev = curr;
    curr = prev->next;
    ++pos;
  }

  SubReverse(s, f);

  s->next = a;
  
  if (p)
  {
    p->next = f;
    return L;
  }
  else
  {
    return f;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
