#ifndef TRIE_H
#define TRIE_H

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_START =  96;
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
    this->val = tolower(val);
  }

  bool has(char character)
  {
    char lowerCasedCharacter = tolower(character);

    return this->get(lowerCasedCharacter) != nullptr;
  }

  void add_child(TrieNode *node)
  {
    char character = node->val;
    char lowerCasedCharacter = tolower(character);

    this->children[int(lowerCasedCharacter) - ALPHABET_START] = node;
  }

  TrieNode* get(char character)
  {
    char lowerCasedCharacter = tolower(character);

    return this->children[int(lowerCasedCharacter) - ALPHABET_START];
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
 
  void insert(string word)
  {
    TrieNode *current_node = this->root;

    for (char c : word)
    {
      // if node has char, point to child
      if (current_node->has(c))
      {
        current_node = current_node->get(c);
      }
      else
      {
        TrieNode *node_to_insert = new TrieNode(c);
        current_node->add_child(node_to_insert);
        current_node = node_to_insert;
      }
    }

    current_node->is_end = true;
  }

  bool lookup(string word)
  {
    TrieNode *current_node = this->root;

    for (char c : word)
    {
      if (current_node->has(c)) 
      {
        current_node = current_node->get(c);
      }
      else
      {
        return false;
      }
    }

    return current_node->is_end;
  }

  void dfs_print()
  {
    this->dfs_print(this->root);
  }

  void dfs_print(TrieNode *node)
  {
    cout << node->val << endl;

    for(auto child: node->children)
    {
      if(child != nullptr)
        dfs_print(child);
    }
  }
};

#endif
