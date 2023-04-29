#include <iostream>
#include <cstdio>

using namespace std;

int n, m;
char c;
int ans;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			cin >> c, ans += (c == '#');
	cout << ans << endl;
	return 0;
}