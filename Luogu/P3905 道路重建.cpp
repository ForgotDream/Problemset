#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, m, d;
int link[105][105];
int ano_link[105][105];
int a, b;
int pre[105][105];

int main() {
	memset(link, 0x3f, sizeof link);
	memset(ano_link, 0x3f, sizeof ano_link);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		link[u][v] = w, link[v][u] = w;;
		ano_link[u][v] = 0, ano_link[v][u] = 0;
	}
	cin >> d;
	for (int i = 1; i <= d; i++) {
		int x, y;
		cin >> x >> y;
		ano_link[x][y] = link[x][y];
		ano_link[y][x] = link[y][x];
	}
	for (int k = 1; k <= n; k++)
		for (int x = 1; x <= n; x++)
			for (int y = 1; y <= n; y++) 
				ano_link[x][y] = min(ano_link[x][y], ano_link[x][k] + ano_link[k][y]);
	cin >> a >> b;
	cout << ano_link[a][b] << endl;
		return 0;
}