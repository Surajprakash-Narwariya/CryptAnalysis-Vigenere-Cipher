#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#ifndef UTIL_H
#define UTIL_H

class Util
{
public:
    vector<int> patternSearching(string &cipherText, int start, string &toSearch);
    string cleanCipherText(const string &cipherText);
    unordered_map<string, vector<int>> getAllSubstringFrequency(string &cipherText, int patternSize);
    unordered_set<int> possibleKeyLength(unordered_map<string, vector<int>> &allSubstring);
    int gcdOfArray(vector<int> &array);
    int gcd(int first, int second);
    vector<int> filterSize(unordered_set<int> &lengths, int leftRange, int rightRange);
    double getICValue(string cipherText, int keySize);
    double calculateICValue(string &str);
    vector<string> generateSubstring(string cipherText, int keySize);
    pair<int, double> calculateMIC2strings(string &A, string &B);
    vector<int> frequencyOf26Chars(string &str);
    void gaussianElimination(vector<vector<double>> &matrix);
};

void Util::gaussianElimination(vector<vector<double>> &matrix)
{
    int n = matrix.size();

    // Forward Elimination
    for (int i = 0; i < n; i++)
    {
        // Make the diagonal element 1 and eliminate below
        for (int k = i + 1; k < n; k++)
        {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = 0; j <= n; j++)
            {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    // Back Substitution
    std::vector<double> solution(n);
    for (int i = n - 1; i >= 0; i--)
    {
        solution[i] = matrix[i][n] / matrix[i][i];
        for (int k = i - 1; k >= 0; k--)
        {
            matrix[k][n] -= matrix[k][i] * solution[i];
        }
    }

    // Output the solution
    std::cout << "Solution:\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << "Variable " << i + 1 << " = " << solution[i] << std::endl;
    }
}

pair<int, double> Util::calculateMIC2strings(string &A, string &B)
{
    vector<int> freqA = frequencyOf26Chars(A);
    vector<int> freqB = frequencyOf26Chars(B);

    vector<double> shiftMIC(26);
    pair<int, double> bestSuitable(-1, 0);

    for (int i = 0; i < 26; i++)
    {
        double t = 0;
        for (int j = 0; j < 26; j++)
        {
            t += freqA[j] * freqB[j];
        }
        t = t / (double)(A.size() * B.size());
        shiftMIC[i] = t;

        if (bestSuitable.second < t)
        {
            bestSuitable.first = i;
            bestSuitable.second = t;
        }

        // Now shift the array B by 1 unit
        int temp = freqB[25];
        for (int i = 25; i > 0; i--)
        {
            freqB[i] = freqB[i - 1];
        }
        freqB[0] = temp;
    }

    return bestSuitable;
}

vector<int> Util::frequencyOf26Chars(string &str)
{
    vector<int> freq(26);
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        freq[(int)str[i] - (int)'A']++;
    }
    return freq;
}

double Util::calculateICValue(string &str)
{
    vector<int> frequencyOfChars = frequencyOf26Chars(str);
    int size = str.size();
    int ICValue = 0;
    for (int i = 0; i < 26; i++)
    {
        int freq = frequencyOfChars[i];
        if (freq > 1)
        {
            ICValue += ((freq) * (freq - 1));
        }
    }
    // cout << ((double)ICValue / (double)(size * (size - 1))) << endl;
    return ((double)ICValue / (double)(size * (size - 1)));
}

vector<string> Util::generateSubstring(string cipherText, int keySize)
{
    // For keysize k, it generates the substring consider ith and (i+k)index characters
    vector<string> substrings(keySize);
    int size = cipherText.size();
    for (int i = 0; i < keySize; i++)
    {
        for (int j = i; j < size; j += keySize)
        {
            substrings[i] += cipherText[j];
        }
    }
    return substrings;
}

double Util::getICValue(string cipherText, int keySize)
{
    // Breaking the string into keysizes
    vector<string> substrings = generateSubstring(cipherText, keySize);

    double ICValue = 0;
    for (int i = 0; i < keySize; i++)
    {
        double val = (double)calculateICValue(substrings[i]);
        ICValue += val;
    }
    return (double)ICValue / (double)keySize;
}

vector<int> Util::filterSize(unordered_set<int> &lengths, int leftRange, int rightRange)
{
    vector<int> filteredkeyLength;
    // Filtering out the choices given by Kasisiki method
    for (auto i : lengths)
    {
        if (i >= leftRange && i <= rightRange)
        {
            filteredkeyLength.push_back(i);
        }
    }

    cout << "POSSIBLE KEY LENGTH SIZE FROM " << leftRange << " to " << rightRange << " is" << " ";
    for (int i : filteredkeyLength)
        cout << i << " ";
    cout << endl;

    return filteredkeyLength;
}

int Util::gcd(int first, int second)
{
    if (second == 0)
        return first;
    return gcd(second, first % second);
}

int Util::gcdOfArray(vector<int> &array)
{
    vector<int> diff;
    // Finding the difference between two occurences of pattern in the cipher text
    for (int i = 1; i < array.size(); i++)
    {
        diff.push_back(array[i] - array[i - 1]);
    }

    // Finding the gcd of the different length for a unique string
    int gcdResult = diff[0];
    for (int i = 1; i < diff.size(); i++)
    {
        gcdResult = gcd(gcdResult, diff[i]);
    }
    return gcdResult;
}

unordered_set<int> Util::possibleKeyLength(unordered_map<string, vector<int>> &allSubstring)
{
    // consider each substring and inserting its value into the array
    vector<int> gcdValues;
    for (auto &v : allSubstring)
    {
        string str = v.first;
        vector<int> freq = v.second;
        int val = gcdOfArray(freq);
        if (val != 1)
            gcdValues.push_back(val);
    }
    cout << endl;

    // Now checking each gcd value to other gcd value such that result is not 1
    unordered_set<int> possibleLength;
    int size = gcdValues.size();
    for (int i = 0; i < size; i++)
    {
        int currentGCD = gcdValues[i];
        for (int j = i + 1; j < size; j++)
        {
            int temp = gcd(currentGCD, gcdValues[j]);
            if (temp != 1)
            {
                currentGCD = temp;
            }
        }
        possibleLength.insert(currentGCD);
    }
    return possibleLength;
}

unordered_map<string, vector<int>> Util::getAllSubstringFrequency(string &cipherText, int patternSize)
{
    unordered_map<string, vector<int>> pattFreq;
    int size = cipherText.size();
    for (int i = 0; i < size - patternSize + 1; i++)
    {
        // construct the pattern string of size 3;
        string patt = "";
        for (int a = i; a < i + patternSize; a++)
            patt += cipherText[a];

        if (pattFreq.find(patt) != pattFreq.end())
        {
            continue;
        }

        vector<int> temp = patternSearching(cipherText, i + 1, patt);
        if (temp.size() > 0)
            pattFreq[patt] = temp;
    }
    return pattFreq;
}

vector<int> Util::patternSearching(string &cipherText, int start, string &pattern)
{
    vector<int> indexes;
    indexes.push_back(start - 1);
    int cipherTextSize = cipherText.size();
    int patternSize = pattern.size();
    for (int i = start; i < cipherText.size() - patternSize + 1; i++)
    {
        bool isMatch = true;
        for (int j = 0; j < patternSize; j++)
        {
            if (cipherText[i + j] != pattern[j])
            {
                isMatch = false;
            }
        }
        if (isMatch)
            indexes.push_back(i);
    }
    return indexes.size() > 1 ? indexes : vector<int>();
}

string Util::cleanCipherText(const string &cipherText)
{
    // Convert the code to the UpperCase
    string text = cipherText;
    for (char &c : text)
        c = toupper(c);

    // Remove the all the spaces and symbols
    string cipher = "";
    for (char c : text)
        if ((int)c >= 65 && (int)c <= 90)
            cipher += c;

    return cipher;
}

#endif