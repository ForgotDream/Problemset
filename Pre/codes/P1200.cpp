#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int M = 47;
string a, b;
int n = 1, m = 1;

int main() {
	cin >> a >> b;
	for (auto i : a) n = (n * (i - 'A' + 1)) % M;
	for (auto i : b) m = (m * (i - 'A' + 1)) % M;
	if (n == m) cout << "GO" << endl;
	else cout << "STAY" << endl;
	return 0;
}