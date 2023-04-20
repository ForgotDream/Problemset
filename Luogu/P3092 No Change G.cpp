#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int K = 20, N = 1e5 + 50, INF = 0x3f3f3f3f;
int k, n;
ll val[K], w[N], sum[N];
int f[1 << K], ans = -1;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> k >> n;
	for (int i = 1; i <= k; i++) cin >> val[i];
	for (int i = 1; i <= n; i++) cin >> w[i], sum[i] = sum[i - 1] + w[i];

	for (int i = 0; i < (1 << k); i++) 
		for (int j = 0; j < k; j++) 
			if (i & (1 << j)) {
				int pivot = upper_bound(sum + 1, sum + n + 1, sum[f[i ^ (1 << j)]] + val[j + 1]) - sum - 1;
				f[i] = max(f[i], pivot);
			}

	for (int i = 0; i < (1 << k); i++)
		if (f[i] == n) {
			int tmp = 0;
			for (int j = 0; j < k; j++)
				if (!(i & (1 << j))) tmp += val[j + 1];
			ans = max(tmp, ans);
		}

	cout << ans << endl;
	return 0;
}