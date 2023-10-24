#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int M = 550;
int a, b;
int graph[M][M];
bool used[M];
int f[M], tmp;

void solve() {
	// for (int i = 1; i <= b; i++) {
		memset(used, 0, sizeof used);
		memset(f, 0x3f, sizeof f);
		tmp = 0;
		int cur = 1;
		f[cur] = 0;
		for (int j = 1; j <= b; j++) {
			int minn = 0x3f3f3f3f;
			for (int k = 1; k <= b; k++)  
				if (!used[k] && minn > f[k]) minn = f[k], cur = k;
			tmp += minn, used[cur] = true;
			// cout << minn << endl;
			for (int k = 1; k <= b; k++) 
				if (!used[k] && f[k] > graph[cur][k]) f[k] = graph[cur][k];
		}
		cout << tmp + a << endl;
	// }
	return;
}

int main() {
	cin >> a >> b;
	for (int i = 1; i <= b; i++)
		for (int j = 1; j <= b; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 0) graph[i][j] = a;
			else graph[i][j] = min(graph[i][j], a);
		}
	solve();
	return 0;
}