#include <bits/stdc++.h>
#include <iostream>
#include "util.h"
using namespace std;

class CryptAnalysis
{
public:
    string cipherText = "";

    CryptAnalysis(string ct)
    {
        cipherText = ct;
    };
    // unordered_set<int> possibleKeySizeByKasaski;

    // Return the possible key size
    unordered_set<int> kasaskiMethod();

    // Return the exact key size that fullfill both Kasaski and IC method
    int indexOfCoincidence(unordered_set<int> &possibleKeySizeByKasaski, int leftRange, int rightRange);

    // Return the key for the decryption
    string mutualIndexOfCoincidence(int keySize);
};

string CryptAnalysis::mutualIndexOfCoincidence(int keySize)
{
    Util util;
    vector<string> substrings = util.generateSubstring(cipherText, keySize);
    cout << endl;
    for (int i = 0; i < substrings.size(); i++)
    {
        for (int j = i + 1; j < substrings.size(); j++)
        {
            pair<int, double> micValue = util.calculateMIC2strings(substrings[i], substrings[j]);
            cout << micValue.first << " " << micValue.second << "\n";
            cout << "K" << i + 1 << " - K" << j + 1 << " = " << micValue.first << endl;
            cout << endl;
        }
    }
    cout << endl;
    // For the ith string, we find the MIC with other susbtring
    return "";
}

int CryptAnalysis::indexOfCoincidence(unordered_set<int> &possibleKeySizeByKasaski, int leftRange, int rightRange)
{
    Util util;
    vector<int> filteredKeys = util.filterSize(possibleKeySizeByKasaski, leftRange, rightRange);

    vector<double> ICValues(11);
    for (int i = 0; i < filteredKeys.size(); i++)
    {
        ICValues[filteredKeys[i]] = util.getICValue(cipherText, filteredKeys[i]);
    }

    cout << endl;
    int maxIndex = 0;
    for (int i = 0; i < 11; i++)
    {
        cout << "For key of size" << i << "  IC VALUE IS " << ICValues[i] << endl;
        if (ICValues[i] > ICValues[maxIndex])
            maxIndex = i;
    }

    return maxIndex;
}

unordered_set<int> CryptAnalysis::kasaskiMethod()
{
    Util util;
    // Remove the characters and space between letters and make it uppercase
    string cipher = util.cleanCipherText(cipherText);
    int patternSize = 3;
    // Return the substring with its repetition index in the cipher text
    unordered_map<string, vector<int>> x = util.getAllSubstringFrequency(cipher, patternSize);

    // Printing the substring
    // for (auto &m : x)
    // {
    //     cout << m.first << " -- ";
    //     for (int i : m.second)
    //         cout << i << " ";
    //     cout << endl;
    // }

    unordered_set<int> plength = util.possibleKeyLength(x);

    cout << endl;

    return plength;
}