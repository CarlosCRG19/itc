#ifndef TRIE_H
#define TRIE_H

#include <cctype>
#include <iostream>
#include <string>
#include <stdexcept>

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

  /**
   * @brief returns if character is a child of a node.
   * Complexity: O(1)
   * 
   * @param character a character to look for in the node
   * @returns true if character is in node, else false
   */
  bool has(char character)
  {
    char lowerCasedCharacter = tolower(character);

    return this->get(lowerCasedCharacter) != nullptr;
  }

  /**
   * @brief adds a child to the node.
   * Complexity: O(1)
   * 
   * @param node a node to add as a child
   */
  void add_child(TrieNode *node)
  {
    char character = node->val;
    char lowerCasedCharacter = tolower(character);

    this->children[int(lowerCasedCharacter) - ALPHABET_START] = node;
  }

  /**
   * @brief gets the child node with value `character`
   * 
   * @param character a character to look for in the node's children nodes
   * @return TrieNode* a pointer to the fetched node
   */
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
    this->root = new TrieNode();
  }
 
  /**
   * @brief inserts a word into the trie.
   * Complexity: O(n). Insertion iterates the length of the word to insert.
   * 
   * @param word a word to insert into the trie.
   */
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

  /**
   * @brief searches a word in the trie.
   * Complexity: O(n). Lookup iterates the length of the word.
   * 
   * @param word 
   * @return true if a sequence of nodes make the word, with and ending node marked as final.
   * @return false otherwise
   */
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

  /**
   * @brief Prints the nodes in the trie, performing DFS.
   * 
   */
  void dfs_print()
  {
    this->dfs_print(this->root);
  }

  /**
   * @brief Recursively prints the nodes in the trie, using DFS.
   * Complexity: O(n). DFS traverses every node in the trie.
   * 
   * @param node 
   */
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
