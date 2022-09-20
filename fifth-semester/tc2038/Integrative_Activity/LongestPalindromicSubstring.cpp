#include <string>
#include <tuple>

using namespace std;

class LongestPalindromicSubstring {
    public:
        static tuple<string, int, int> solve(string &s1){
            string s1Extended;
        
            // Create extended version of string with center between letters
            for(int i=0 ; i < s1.size() ; i++)
                s1Extended += "#" + s1.substr(i,1);
            s1Extended.push_back('#');

            vector<int> lps(s1Extended.size(), 0);
            
            int C = 0, R = 0, palindromeCenter = 0, maxLength = 0;
            for(int i=1 ; i < s1Extended.size()-1 ;i++) {
                int iMirror = 2*C - i;

                if (R > i) {
                    lps[i] = min(lps[iMirror], R - i);
                } else {
                    lps[i] = 0;
                }

                while(i - (1 + lps[i]) >= 0 && i + (1 + lps[i]) <= s1Extended.size() && s1Extended[i - (1 + lps[i])] == s1Extended[i + (1 + lps[i])])
                    lps[i]++;

                if(i + lps[i] > R) {
                    C = i;
                    R = i + lps[i];
                }

                if(lps[i] > maxLength) {
                    maxLength = lps[i];
                    palindromeCenter = i;
                }    
            }

            int initialPosition = (palindromeCenter - maxLength) / 2;
            int finalPosition = initialPosition + maxLength;

            string palindrome = s1.substr(initialPosition, maxLength);

            // +1 is added as we start counting with first column as 1.
            return { palindrome, initialPosition + 1, finalPosition };
        }
};
