#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <unordered_map>

using TPrice = int;
using TISBN = int;

using TLRU = std::list<TISBN>;
using TLRUIter = TLRU::const_iterator;

struct CacheItem
{
	TPrice price;
	TLRUIter iter;
};

using TCache = std::unordered_map<TISBN, CacheItem>;
using TCacheIter = TCache::iterator;

class LruCache {
  int cacheSize;
public:  
  LruCache(size_t capacity) : cacheSize(capacity) {}  

  void MoveUp(TCacheIter& iter)
  {
		lru.erase(iter->second.iter);
		lru.push_front(iter->first);
		iter->second.iter = lru.begin();
  }

  void TryReduceCache()
  {
    if (lru.size() > cacheSize)
    {
      auto& isbn = lru.back();
      cache.erase(isbn);
      lru.pop_back();
    }
  }

  int Lookup(TISBN isbn) {
    
    auto iter = cache.find(isbn);
    if (iter != cache.end())
    {
      lru.erase(iter->second.iter);
      lru.push_front(iter->first);
      iter->second.iter = lru.begin();
      return iter->second.price;
    }

    return -1;
  }
  void Insert(TISBN isbn, TPrice price) {
    auto iter = cache.find(isbn);
    if (iter != cache.end())
    {
      MoveUp(iter);
    }
    else
    {
      lru.push_front(isbn);
      cache.emplace(isbn, CacheItem{ price,lru.begin() });
      TryReduceCache();
    }

    return;
  }
  bool Erase(TISBN isbn) {
    auto iter = cache.find(isbn);
    if(iter != cache.end())
    {
      lru.erase(iter->second.iter);
      cache.erase(iter);
      return true;
    }

    return false;
  }

private:
  TCache cache;
  TLRU lru;
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
