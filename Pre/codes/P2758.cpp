#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

char a[2050], b[2050];
int f[2050][2050];
int la, lb;

void solve() {
	la = strlen(a), lb = strlen(b);
	for (int i = 1; i <= la; i++) f[i][0] = i;
	for (int i = 1; i <= lb; i++) f[0][i] = i;
	for (int i = 1; i <= la; i++) {
		for (int j = 1; j <= lb; j++) {
			if (a[i - 1] == b[j - 1]) {
				f[i][j] = f[i - 1][j - 1];
			} else {
				f[i][j] = min(f[i - 1][j - 1], min(f[i][j - 1], f[i - 1][j])) + 1;
			}
		}
	}
	cout << f[la][lb] << endl;
	return;
}

int main() {
	cin >> a >> b;
	solve();
	return 0;
}