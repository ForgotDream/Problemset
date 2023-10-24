#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int ans;
string a, b;

int main() {
	cin >> a >> b;
	for (int i = 0; i < a.length(); i++) 
		for (int j = 1; j < b.length(); j++)
			if (a[i] == b[j] && a[i + 1] == b[j - 1]) 
				ans++;
	cout << static_cast<long long>(1 << ans) << endl;
	return 0;
}