#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50, INF = 0x3f3f3f3f;
int n;
int myPrice[N];
int f[N], way[N][N];
bool minCost[N];
i64 g[N];
int a, b, c;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	memset(way, -1, sizeof(way));

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> f[i];
		g[i] = 1;
	}
	while (cin >> a >> b >> c) {
		way[a][b] = c;
		way[b][a] = c;
	}

	for (int i = 0; i < n; i++) {
		int pivot, maxx = INF;
		for (int j = 0; j < n; j++) {
			if (!minCost[j] && f[j] < maxx) {
				pivot = j;
				maxx = f[j];
			}
		}
		minCost[pivot] = true;

		for (int j = 0; j < n; j++) {
			if (minCost[j] && ~way[pivot][j]) {
				int tgt = way[pivot][j];
				if (f[pivot] + f[j] < f[tgt]) {
					f[tgt] = f[pivot] + f[j];
					g[tgt] = g[pivot] * g[j];
				} else if (f[pivot] + f[j] == f[tgt]) {
					g[tgt] += g[pivot] * g[j];
				}
			}
		}
	}

	cout << f[0] << ' ' << g[0] << '\n';

	return 0;
}
