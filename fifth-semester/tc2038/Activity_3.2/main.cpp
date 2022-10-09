#include <iostream>
#include <string>

#include "Trie.h"

using namespace std;

int main()
{
  int n; cin >> n;

  Trie myTrie;

  while (n > 0) {
    string word; cin >> word;
    myTrie.insert(word);
    n--;
  }

  int m; cin >> m;

  while (m > 0) {
    string word; cin >> word;
    cout << myTrie.lookup(word) << endl;
    m--;
  }
}
