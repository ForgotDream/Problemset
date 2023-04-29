#include <iostream>
#include <cstdio>

using namespace std;

const int N = 35, M = 35;
int n, m;
int canSol[N];
int ans;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			if (c == 'o') canSol[i] = canSol[i] + (1 << (j - 1));
		}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if ((canSol[i] | canSol[j]) == (1 << (m)) - 1) ans++;
	cout << ans << endl;
	return 0;
}