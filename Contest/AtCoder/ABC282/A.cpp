#include <iostream>
#include <cstdio>

using namespace std;

int n;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cout << (char)('A' + i);
	cout << endl;
	return 0;
}