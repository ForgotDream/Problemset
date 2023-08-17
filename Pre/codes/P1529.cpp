#include <iostream>
#include <cstdio>
#include <vector>
#include <cctype>
#include <cstring>

#define h q[head]

using namespace std;

int n, ans = 0x3f3f3f3f, k;
int f[100][100];

void solve() {
	for(int i = 1; i<=52; i++) 
		for(int j = 1; j<=52; j++) 
			for(int k = 1; k<=52; k++)
				f[j][k] = min(f[j][k], f[j][i] + f[i][k]);
	for(int i = 27; i<=51; i++) 
		if(ans > f[52][i]) ans = f[52][i], k = i;		
	cout << (char)(k + 'A' - 27) << ' ' << ans << endl;
	return;
}

int main() {
	cin >> n;
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++) {
		char x, y;
		int a, b, z;
		cin >> x >> y >> z;
		if (isupper(x)) a = x - 'A' + 27;
		else a = x - 'a' + 1;
		if (isupper(y)) b = y - 'A' + 27;
		else b = y - 'a' + 1;
		// v[a].push_back({b, z}), v[b].push_back({a, z});
		f[a][b] = min(f[a][b], z), f[b][a] = min(f[b][a], z);
	}

	solve();

	return 0;
}