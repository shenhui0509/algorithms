#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

constexpr int char_nums = 26;


struct trie_node {
  int cnt;
  trie_node *childs[char_nums];
  trie_node():
    cnt(0)
  {
    std::uninitialized_fill_n(childs, char_nums, nullptr);
  }
};

using std::string;

class Trie
{
public:
  Trie():root(new trie_node){}
  ~Trie()
  {
    if(!root)
      return;
    destory_sub_trie(root);
  }

  void feed(const string &word)
  {
    auto it = word.begin();
    auto p = root;
    for(; it != word.end(); ++it){
      if(p->childs[*it - 'a'] == nullptr){
        p->childs[*it - 'a'] = new trie_node;
      }
      p = p->childs[*it - 'a'];
      ++p->cnt;
    }
  }

  int query(const string &word)
  {
    auto p = root;
    auto it = word.begin();
    for(; it != word.end(); ++it){
      if(p->childs[*it - 'a'] == nullptr)
        return 0;
      p = p->childs[*it - 'a'];
    }
    return p->cnt;
  }
private:
  void destory_sub_trie(trie_node *node)
  {
    for(int i = 0; i < char_nums; ++i){
      if(node->childs[i] != nullptr)
        destory_sub_trie(node->childs[i]);
    }
    delete node;
  }

  trie_node *root;
};

int main()
{
  string dict[] = {"babab", "babbaaaa","abba","aaaaabaa","babaababb"};
  string queries[] = {"babb","baabaaa","bab","bb","bbabbaab"};
  Trie trie;
  std::for_each(dict, dict + 5, [&trie](const string &s)
      {
        trie.feed(s);
      });
  std::transform(queries, queries + 5, std::ostream_iterator<int>(std::cout, " "),
      [&trie](const string &s)
      {
        return trie.query(s);
      });
  std::cout << "-------------\n";
}
