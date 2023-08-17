#include <iostream>

using namespace std;
using i64 = long long;

static const int N = 600;
int n, m, t;
int bucket[N], table[N][N];
int opposite[N], pivot, tmp;
int mp[N];

int main() {
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	// cin >> n;
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		cin >> opposite[i];
		if (m == opposite[i]) {
			pivot = i;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			table[i][j] = ((n - j - i + 1) % n + n) % n + 1;
			// cerr << table[i][j] << ' ';
		}
		// cerr << '\n';
	}
	
	for (int i = 1; i <= n; i++) {
		if (table[i][pivot] == i) {
			bucket[m] = i;
			tmp = i;
			break;
		}
	}
	for (int i = 1; i <= n; i++) {
		bucket[opposite[i]] = table[tmp][i];
		mp[table[tmp][i]] = opposite[i];
		// cerr << opposite[i] << ' ' << table[tmp][i] << '\n';
	}
	for (int i = 1; i <= n; i++) {
		if (bucket[opposite[t]] == table[i][bucket[m]]) {
			tmp = i;
			break;
		}	
	}
	
	// cerr << tmp << '\n';
	
	for (int i = 1; i <= n; i++) {
		cout << mp[table[tmp][mp[i]]] << ' ';
	}
	
	return 0;
}
