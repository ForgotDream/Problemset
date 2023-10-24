#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
	cin >> s;
	for (auto ch : s) {
		if (ch == '0') cout << '1';
		else cout << '0';
	}
	return 0;
}