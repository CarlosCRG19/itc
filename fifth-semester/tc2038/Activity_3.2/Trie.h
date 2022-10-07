#include <unordered_map>
#include <string>

#ifndef TRIE_H
#define TRIE_H

struct TrieNode {
  char val;
  std::unordered_map<char, TrieNode> children;
};

class Trie {

  TrieNode root;

  bool insert(std::string word);
  bool lookup(std::string word);

};

#endif