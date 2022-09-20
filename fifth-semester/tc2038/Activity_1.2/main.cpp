#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

// Even though the approach presented in this algorithm is the most intuitive one,
// it is error prone as choosing the highest denomination might not always involve
// using the least amount of coins.
vi calculateCoinChangeWithGreedyAlgorithm(int amount, vi coinDenominations) {
  vi reverseSortedCoinDenominations = coinDenominations;
  sort(reverseSortedCoinDenominations.begin(), reverseSortedCoinDenominations.end(), greater<int>());

  vi minimumCoinChange;

  for (int denomination : reverseSortedCoinDenominations) {
    while (amount >= denomination) {
      amount -= denomination;
      minimumCoinChange.push_back(denomination);
    }
  }

  return minimumCoinChange;
}

vi calculateCoinChangeWithDynamicProgramming(int amount, vi coinDenominations) {
  vi sortedCoinDenominations = coinDenominations;
  sort(sortedCoinDenominations.begin(), sortedCoinDenominations.end());

  vector<vi> minimumCoinChange(amount + 1);
  // Instead of using INT_MAX, we populate the array with
  // `amount + 1` as that value cannot be reached as well.
  vi memoizationArray(amount + 1, amount + 1);

  // Base case
  memoizationArray[0] = 0;

  for (int i=1 ; i<=amount ; i++) {
    for (int denomination : sortedCoinDenominations) {
      int remainder = i - denomination;

      if (denomination <= i && (memoizationArray[remainder] + 1) < memoizationArray[i]) {
        memoizationArray[i] = memoizationArray[remainder] + 1;

        minimumCoinChange[i] = minimumCoinChange[remainder];
        minimumCoinChange[i].push_back(denomination);
      }
    }
  }

  if (memoizationArray[amount] == amount + 1) {
    // Case could not be solved;
    // return empty array.
    return vi();
  }

  return minimumCoinChange[amount];
}

// Function directly coupled to the format of the homework.
void outputAnswer(vi coinChange) {
  if (coinChange.size() == 0) {
    cout << "This case does not have an answer through this method\n";
    return;
  }

  map<int, int, greater<int>> coinsUsedByDenomination;

  for (int denomination : coinChange) {
    coinsUsedByDenomination[denomination]++;
  }

  for (auto pair : coinsUsedByDenomination) {
    cout << "Denomination: " << pair.first << "; Coins Used: " << pair.second << "\n";
  }
}

int main() {
  int N, P, Q;
  cin >> N;

  vi coinDenominations(N);
  for (int i=0 ; i<N ; i++) {
    cin >> coinDenominations[i];
  }

  cin >> P >> Q;

  int change = Q - P;

  vi greedyAlgorithmResult = calculateCoinChangeWithGreedyAlgorithm(change, coinDenominations);
  vi dynamicProgrammingResult = calculateCoinChangeWithDynamicProgramming(change, coinDenominations);

  cout << "Greedy Algorithm: \n";
  outputAnswer(greedyAlgorithmResult);

  cout << "\n";

  cout << "Dynamic Programming: \n";
  outputAnswer(dynamicProgrammingResult);

  return 0;
}
