#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 20, INF = 0x3f3f3f3f;
const double EPS = 1e-8;
int T, n, m;
double x[N], y[N];
int f[1 << N], status[N * N], cnt;

void solve() {
	memset(f, 0x3f, sizeof f), f[0] = 0;
	for (int i = 0; i <= (1 << n) - 1; i++) 
		for (int j = 1; j <= cnt; j++)
			f[i | status[j]] = min(f[i | status[j]], f[i] + 1);
	cout << f[(1 << n) - 1] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> T;
	while (T--) {
		cin >> n >> m, cnt = 0;
		for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++) {
				if (fabs(x[i] - x[j]) < EPS) continue;
				double a, b, t1, t2, t3;
				t1 = x[i] * x[j] * (x[i] - x[j]);
				t2 = x[j] * y[i], t3 = x[i] * y[j];
				a = (t2 - t3) / t1, b = (t3 * x[i] - t2 * x[j]) / t1;
				if (a >= -EPS) continue;
				status[++cnt] = 0;
				for (int k = 1; k <= n; k++) 
					if (fabs(a * x[k] * x[k] + b * x[k] - y[k]) < EPS) 
						status[cnt] |= 1 << (k - 1);
 			}
 		for (int i = 1; i <= n; i++) status[++cnt] = 1 << (i - 1);
 		solve();
	}	
	return 0;
}