#include <string>
#include <tuple>

using namespace std;

class LongestCommonSubstring {
    class SolutionStore {
        private:
            int length = 0;
            int finalPositionInFirstFile = 0;
            int finalPositionInSecondFile = 0;

        public:
            void setValues(int _length, int _finalPositionInFirstFile, int _finalPositionInSecondFile) {
                length = _length;
                finalPositionInFirstFile = _finalPositionInFirstFile;
                finalPositionInSecondFile = _finalPositionInSecondFile;
            }

            int getLength() {
                return length;
            }

            tuple<string, pair<int, int>, pair<int, int>> getSolution(string &s1) {
                int initialPositionInFirstFile = finalPositionInFirstFile - length + 1;
                int initialPositionInSecondFile = finalPositionInSecondFile - length + 1;

                // We add +1 because we are not using 0 indexed values.
                pair<int, int> firstFilePositions = make_pair(initialPositionInFirstFile, finalPositionInFirstFile);
                pair<int, int> secondFilePositions = make_pair(initialPositionInSecondFile, finalPositionInSecondFile);

                string substring = s1.substr(initialPositionInFirstFile, length);

                return { substring, firstFilePositions, secondFilePositions };
            }
    };

    public:
        static tuple<string, pair<int, int>, pair<int, int>> solve(string &s1, string &s2){
            int n = s1.length(), m = s2.length();
            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

            SolutionStore solutionStore;

            for (int i=1 ; i<=n ; i++) {
                for (int j=1 ; j<=m ; j++) {
                    if (s1[i-1] == s2[j-1]) {
                        int lengthSoFar = dp[i-1][j-1] + 1;

                        dp[i][j] = lengthSoFar;

                        if (lengthSoFar > solutionStore.getLength()) {
                            solutionStore.setValues(lengthSoFar, i-1, j-1);
                        }
                    }
                }
            }

            return solutionStore.getSolution(s1);
        }
};
