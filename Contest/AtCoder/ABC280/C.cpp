#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string s, t;

int main() {
	cin >> s >> t;
	for (int i = 0; i < s.length(); i++) 
		if (s[i] != t[i]) return cout << i + 1 << endl, 0;
	cout << s.length() + 1 << endl;
	return 0;
}