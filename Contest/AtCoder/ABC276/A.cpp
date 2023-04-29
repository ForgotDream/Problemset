#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string s;
int ans = -1;

int main() {
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'a') ans = i + 1;
	}
	cout << ans << endl;
	return 0;
}