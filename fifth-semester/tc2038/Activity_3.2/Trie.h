#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <string>


int ALPHABET_START =  96;
const int ALPHABET_SIZE = 27;

class TrieNode
{
public:
  char val;
  bool is_end;
  TrieNode* children[ALPHABET_SIZE];

  TrieNode()
  {
    this->val = '\0';
  }
  TrieNode(char val)
  {
    this->val = val;
  }

  bool has(char character)
  {
    return this->get(character) != nullptr;
  }

  void add_child(TrieNode *node)
  {
    char character = node->val;
    this->children[int(character) - ALPHABET_START] = node;
  }

  TrieNode *get(char character)
  {
    return this->children[int(character) - ALPHABET_START];
  }
};

class Trie
{
public:
  TrieNode* root;

  Trie()
  {
    this->root = new TrieNode('@');
  }
  
  void insert(std::string word);
  bool lookup(std::string word);
  void dfs_print();

private:
  void dfs_print(TrieNode *node);
};

// develop
void Trie::insert(std::string word)
{
  TrieNode *current_node = this->root;
  for (auto i : word)
  {
    // if node has char, point to child
    if (current_node->has(i))
    {
      current_node = current_node->get(i);
    }
    else
    {
      TrieNode *node_to_insert = new TrieNode(i);
      current_node->add_child(node_to_insert);
      current_node = node_to_insert;
    }
  }
  current_node->is_end = true;
}

bool Trie::lookup(std::string word)
{
  TrieNode *current_node = this->root;
  for (auto i : word)
  {
    if (current_node->has(i)) 
    {
      current_node = current_node->get(i);
    }
    else
    {
      return false;
    }
  }
  return current_node->is_end;
}

void Trie::dfs_print()
{
  this->dfs_print(this->root);
}

void Trie::dfs_print(TrieNode *node)
{
  std::cout << node->val << std:: endl;
  for(auto i: node->children)
  {
    if(i != nullptr)
      dfs_print(i);
  }
}

#endif