#include <bits/stdc++.h>
#include <iostream>
#include "cryptanalysis.h"
#include "util.h"
using namespace std;

int main()
{
	cout << endl;
	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);

	// string cipher = "Ar c zmwvjari aaxa jazgb s qcl feocv Pgm olq usw cjoeaq ar c fmvtw. Zmu jajg usw c uzmtjompb gj ocwxklyw, fcshngfiu, yfh glvpgqk xq-bg pkqlw. Hpgq fyor wllmn bmwm, fw qqtwh vfjswez xjc vea jaog y eeefarg, psvgjq tcskmpe ls eylgj faw dpwevf. Wzgpq qqpfmpe, zi ymmpf pmwj mmx qd zmu yhetreipr, tvkcxgcqw mp fsrf, yfh fgni klls vfw gjygw qd llg aaxa. Mfi fyq, eu Jws yyk lwpjckly xq ugvm, fw rqraggb sr qjv aqksr uglxkly sp y tipaz fa rzi ryjo, hcwhkly xjc tmtbk. Wjc oeu rzitc wzgpq qqpfmpe, spyyqw ygll c nweecxyn qemnc gr jcj jcaw. Fwr gr vfaw ryjxkampcp vea, qgqgrzmpe sfqsl lgp uewezx Ncg’w crliprasp";

	string cipher;
	getline(cin, cipher);

	Util util;
	string cipherText = util.cleanCipherText(cipher);

	CryptAnalysis c(cipherText, cipher);
	unordered_set<int> val = c.kasaskiMethod();
	int keySize = c.indexOfCoincidence(val, 2, 10);

	cout << endl;
	cout << "FINALISED KEY SIZE IS --    " << keySize << endl;
	cout << endl;

	vector<string> keysList = c.mutualIndexOfCoincidence(keySize);
	for (const string &i : keysList)
	{
		cout << i << " ";
	}
	return 0;
};
