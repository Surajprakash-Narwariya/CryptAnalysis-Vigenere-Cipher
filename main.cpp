#include <bits/stdc++.h>
#include <iostream>
#include "cryptanalysis.h"
#include "util.h"
using namespace std;

int main()
{
	cout << endl;
	freopen("output.txt", "w", stdout);

	string cipher = "kbduwwhxxwopcuhfahkitwyithkitszeuoflcfpmpuomvhoidcrouhrvghkevadradhsrzhpqjhhGjhvardcvvhsybhvifhivsggwgwsosuwywwlckdvogpmnsdrfoivksqhnmzstrWlggkinjhwysuihwopgrzmvvvxqfliutusoouswbgxjszstzgmpjlxkbjvgogitgwsglspqfhrgkdhxsqxwfhwcbgmfsdw";

	Util util;
	string cipherText = util.cleanCipherText(cipher);

	CryptAnalysis c(cipherText);
	unordered_set<int> val = c.kasaskiMethod();
	int keySize = c.indexOfCoincidence(val, 2, 10);

	cout << endl;
	cout << "FINALISED KEY SIZE IS --    " << keySize << endl;
	cout << endl;

	c.mutualIndexOfCoincidence(keySize);

	vector<vector<double>> matrix = {
		{1, -1, 0, 0, 14}, // Equation 1: 2x - y + 3z = 9
		{1, 0, -1, 0, 25}, // Equation 2: 3x + 2y - 4z = -6
		{1, 0, 0, -1, 24},
		{0, 1, -1, 0, 11} // Equation 3: x + y + z = 7
	};

	util.gaussianElimination(matrix);

	return 0;
};
