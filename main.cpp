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
	return 0;
};
