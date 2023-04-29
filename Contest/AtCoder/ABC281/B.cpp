#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;

string s;
long long sum;

int main() {
	cin >> s;
	if (s.length() != 8) return cout << "No" << endl, 0;
	// cout << 1 << endl;
	for (int i = 0; i < s.length(); i++) {
		if (i == 0) {
			if (!isupper(s[i])) return cout << "No" << endl, 0;
		}
		else if (i == s.length() - 1) {
			if (!isupper(s[i])) return cout << "No" << endl, 0;
		}
		else {
			if (!isdigit(s[i])) return cout << "No" << endl, 0;
			if (i == 1) {
				if (s[i] == '0') return cout << "No" << endl, 0;
			}
			sum = sum * 10 + s[i] - '0';
			if (sum > 999999) return cout << "No" << endl, 0;
		}
	}
	if (sum >= 100000 && sum <= 999999) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
