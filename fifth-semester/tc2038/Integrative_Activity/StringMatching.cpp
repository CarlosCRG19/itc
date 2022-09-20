#include <string>
#include <vector>
#include <cstring>

using namespace std;

class StringMatching {
    public:
        static bool KMPSearch(string text, string pattern) {
            int N = text.size();
            int M = pattern.size();

            vector<int> lps;

            for (int i = 0 ; i < M ; i++) {
                lps.push_back(0);
            }

            computeLPSArray(pattern, M, lps);

            int i = 0;
            int j = 0;
            
            bool foundMaliciousCode = false;
            while(i < N){
                if(text[i] == pattern[j]) {
                    i++;
                    j++;
                } else {
                    if (j != 0) { //if the current j index is different of 0 (we need this or it will crash) this will happen if in the first in the first comparison between the current j index letter is different of the i index letter
                        j = lps[j-1]; //Where to start in the lps table the next comaprison (the index of our text)
                    } else {
                        i++; 
                    }
                }
                if(j == M){
                    j = lps[j-1]; // Get all the string matches, not just the first one
                    foundMaliciousCode = true;
                }
            } 
            return foundMaliciousCode;
        }

        static void computeLPSArray(string pattern, int M, vector<int> &lps) {
            int len = 0; //The current max length of the prefix
            // The i index will tell us the current pattern character to comapre
            int i = 1; //The first index to compare in our pattern
            lps[0] = 0;

            // While the current character index is less than the size of the pattern
            while (i < M) {
                if (pattern[i] == pattern[len]) {
                    lps[i] = len + 1;
                    len++;
                    i++;
                } else {
                    if (len != 0) {
                        len = lps[len-1];
                    } else {
                        lps[i] = 0;
                        i++;
                    }
                }
            }
        }

        static bool solve(string text, string pattern){
            return KMPSearch(text, pattern);
        }
};