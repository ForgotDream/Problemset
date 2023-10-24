#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

string a, b;

int main() {
	cin >> a >> b;
	if (a.find(b, 0) != string::npos) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}