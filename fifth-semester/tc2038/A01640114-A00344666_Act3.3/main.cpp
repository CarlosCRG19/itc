#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

/**
 * @brief solves the KnapSack, given N items of values values[] and weights weights[], and a maximum capacity W.
 * Complexity: O(nW), a dp 2d-array of size n x W is built and traversed.
 *  
 * @param N The number of different values
 * @param values The array of values
 * @param weights The weights of 
 * @param W 
 * @return int 
 */
int knapSack(int N, int values[], int weights[], int W) {
  if (N == 0 || W == 0) return 0;

  vector<vi> dp(N+1, vi(W+1, 0));

  for (int i=1 ; i <= N ; i++) {
    for (int w=1 ; w <= W ; w++) {
      if (weights[i-1] <= w)
        dp[i][w] =  max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
      else
        dp[i][w] = dp[i-1][w];
    }
  }

  return dp[N][W];
}

int main() {
  int N; cin >> N;

  int values[N], weights[N];

  for (int i=0 ; i<N ; i++) {
    cin >> values[i];
  }

  for (int j=0 ; j<N ; j++) {
    cin >> weights[j];
  }

  int W; cin >> W;

  cout << knapSack(N, values, weights, W) << '\n';

  return -1;
}
