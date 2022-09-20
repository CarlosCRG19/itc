#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "StringMatching.cpp"
#include "LongestCommonSubstring.cpp"
#include "LongestPalindromicSubstring.cpp"

using namespace std;

string getFileContentAsString(string filePath){
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        cout << "Could not open the file - '" 
            << filePath << "'" << endl; 
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();

    return buffer.str();
}

int main(){
    vector<string> transmissions;
    vector<string> maliciousCodes;

    vector<string> transmissionsFilePaths = { "transmission1.txt", "transmission2.txt" };
    vector<string> maliciousCodesFilePaths = { "mcode1.txt", "mcode2.txt", "mcode3.txt" };

    for (string path : transmissionsFilePaths) {
        transmissions.push_back(getFileContentAsString(path));
    }

    for (string path : maliciousCodesFilePaths) {
        maliciousCodes.push_back(getFileContentAsString(path));
    }
    cout << "---| Integrative Activity 1 |---\n";

    cout << "\nPart 1 - String Matching:\n";
    for(string transmission : transmissions) {
        for (string maliciousCode : maliciousCodes) {
            cout << "\t -> Is malicious code present in transmission?: " << boolalpha << StringMatching::solve(transmission, maliciousCode) << "\n";  
        }
    }

    cout << "\nParte 2 - Longest Palindromic Substring:\n";
    for(string transmission : transmissions) {
        auto [palindrome, initialPosition, finalPosition] = LongestPalindromicSubstring::solve(transmission);

        cout << "\t -> Palindrome found: " << palindrome << " ; initialPosition: " << initialPosition << " ; finalPosition: " << finalPosition << ".\n";
        
    }

    cout << "\nParte 3 - Longest Common Substring:\n";
    string substring;
    pair<int, int> firstFilePositions, secondFilePositions;

    tie(substring, firstFilePositions, secondFilePositions) = LongestCommonSubstring::solve(transmissions[0], transmissions[1]);

    cout << "\t -> Substring found: " << substring;
    cout << "\t -> Positions in first file: " << firstFilePositions.first  << " " << firstFilePositions.second << ".\n";  
    cout << "\t -> Positions in second file: " << secondFilePositions.first  << " " << secondFilePositions.second << ".\n";  

    return 0;
}
