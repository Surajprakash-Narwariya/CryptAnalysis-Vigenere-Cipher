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
    vector<string> mutualIndexOfCoincidence(int keySize);

    // string findFinalKeyword(unordered_set<string> keysList);
};

vector<string> CryptAnalysis::mutualIndexOfCoincidence(int keySize)
{
    Util util;
    vector<string> substrings = util.generateSubstring(cipherText, keySize);
    cout << endl;
    vector<vector<int>> equations;
    int key[keySize];key[0]=0;
    for (int i = 1; i < keySize; i++)
    {
        key[i]=-1;
    }
    
    for (int i = 0; i < substrings.size(); i++)
    {
        for (int j = i + 1; j < substrings.size(); j++)
        {
            pair<int, double> micValue = util.calculateMIC2strings(substrings[i], substrings[j]);
            cout << micValue.first << " " << micValue.second << "\n";
            cout << "K" << i << " - K" << j << " = " << micValue.first << endl;
            vector<int> equation = {i,j,micValue.first};
            equations.push_back(equation);
            cout << endl;
        }
    }
    for (int i = 0; i < equations.size(); i++){
        cout << equations[i][0] << " " << equations[i][1] << " " << equations[i][2] << " ";
    }
    int count=1;
    for (int i = 0; i < equations.size(); i++)
    {
        if(equations[i][0] == 0){
            // cout << equations[i][0] << equations[i][1] << equations[i][2] << endl;
            key[equations[i][1]] = equations[i][2];
            count++;
        }
    }
    for (int i = 0; i < equations.size() && count<=keySize; i++){
        if((key[equations[i][0]] != 0) && (key[equations[i][0]] != -1) && (key[equations[i][1]] == -1)){
            count++;
            key[equations[i][1]] == key[equations[i][0]] + equations[i][2];
        }
        else if((key[equations[i][1]] != 0) && (key[equations[i][0]] == -1) && (key[equations[i][1]] != -1)){
            count++;
            key[equations[i][0]] == abs(key[equations[i][1]] - equations[i][2]);
        }
        else{
            continue;
        }
    }
    cout << endl << key[0] <<" ";
    for (int i = 1; i < keySize; i++){
        key[i]=26-key[i];
        cout << key[i] << " ";
    }
    string finalKey;
    vector<string> keysList;
    for (int i = 0; i < 26; i++){
        int testKey[keySize];finalKey="";
        for(int j=0;j<keySize;j++){
            testKey[j] = (key[j]+i)%26;
        }
        for(int j=0;j<keySize;j++){
            finalKey += static_cast<char>(testKey[j]+65);
        }
        // double finalKeyIC = util.getICValue(cipherText,5);
        // cout << finalKey << " "<<finalKeyIC << endl;
        keysList.push_back(finalKey);
    }
    
    // cout << equations[4][1] << endl;
    cout << endl;
    // For the ith string, we find the MIC with other susbtring
    cout<<cipherText<<endl;
    for(int i=0;i<26;i++){
        string testKey = keysList[i];
        cout << testKey<< " " ;
        string plainText="";
        for (int j = 0; j < cipherText.size();){
            for (int k = 0; k < 4; k++,j++){
                char plain = ((cipherText[j] - 'A') -(testKey[k]-'A')+26)%26 + 'A';
                plainText += plain;
            }
        }
        // vector<int> frequencyOfChars = util.frequencyOf26Chars(plainText);
        // double icValue; int n= cipherText.size();
        // for(int i=0;i<26;i++){
        //     icValue += (frequencyOfChars[i])*(frequencyOfChars[i]-1);
        // }
        // icValue = icValue/(n*(n-1));
        cout <<" "<< plainText<< " "<<endl;
        cout<<endl;
    }

    return keysList;
}

// string CryptAnalysis::findFinalKeyword(unordered_set<string> keysList){
    // string plainText;
    // for(int i=0;i<26;i++){
    //     for (int j = 0; j < cipherText.size(); j++){
    //         for (int k = 0; k < 5; k++){
    //             plainText[j] = cipherText[j] 
    //         }
    //     }
    // }
    // return " ";
// }

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