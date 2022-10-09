#include <iostream>
#include <unordered_map>
#include "Trie.h"

int main()
{
  Trie trie_one;
  trie_one.insert("develop");
  trie_one.insert("developer");
  
  // std::cout << trie_one.lookup("developerr") << std::endl;
  trie_one.dfs_print();
  
}