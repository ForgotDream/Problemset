#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
const ll MOD = 1e9 + 7;
int n, m;
ll tree[N << 2][13], a[N], add[N << 2], ass[N << 2], tmp[13], C[13][13], x;
int opt, l, r;

inline void getC() {
	C[0][1] = 1;
	for (int i = 1; i <= 10; i++) {
		C[i][1] = 1;
		for (int j = 2; j <= i + 1; j++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	return;
}

inline void pushup(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	for (int i = 0; i <= 10; i++) tree[u][i] = (tree[lc][i] + tree[rc][i]) % MOD;
	return;
}

inline void pushdown(int l, int r, int u) {
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (~ass[u]) {
		tmp[0] = 1;
		for (int i = 1; i <= 10; i++) tmp[i] = (tmp[i - 1] * ass[u]) % MOD;

		for (int i = 0; i <= 10; i++)
			tree[lc][i] = (tmp[i] * (mid - l + 1)) % MOD, tree[rc][i] = (tmp[i] * (r - mid)) % MOD;

		ass[lc] = ass[rc] = ass[u], ass[u] = -1;
		add[u] = 0;
	}
	if (add[u]) {
		tmp[0] = 1;
		for (int i = 1; i <= 10; i++) tmp[i] = (tmp[i - 1] * add[u]) % MOD;

		for (int i = 10; ~i; i--) {
			ll curl = 0, curr = 0;
			for (int j = 1; j <= i + 1; j++) {
				curl = (curl + C[i][j] * tree[lc][j - 1] % MOD * tmp[i - j + 1] % MOD) % MOD;
				curr = (curr + C[i][j] * tree[rc][j - 1] % MOD * tmp[i - j + 1] % MOD) % MOD;
			}
			tree[lc][i] = curl % MOD, tree[rc][i] = curr % MOD;
		}

		add[lc] += add[u], add[rc] += add[u], add[u] = 0;
	}
	return;
}

void build(int l, int r, int u) {
	ass[u] = -1;
	if (l == r) {
		tree[u][0] = 1;
		for (int i = 1; i <= 10; i++) tree[u][i] = (tree[u][i - 1] * a[l]) % MOD;
		return;
	}
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, ll num) {
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (l <= s && t <= r) {
		if (~ass[u]) {
			tmp[0] = 1;
			for (int i = 1; i <= 10; i++) tmp[i] = (tmp[i - 1] * ass[u]) % MOD;
			for (int i = 0; i <= 10; i++)
				tree[lc][i] = (mid - s + 1) * tmp[i] % MOD, tree[rc][i] = (t - mid) * tmp[i] % MOD;
			ass[u << 1] = ass[u << 1 | 1] = ass[u], ass[u] = -1;
		}
		tmp[0] = 1;
		for (int i = 1; i <= 10; i++) tmp[i] = (tmp[i - 1] * num) % MOD;
		for (int i = 10; ~i; i--) {
			ll cur = 0;
			for (int j = 1; j <= i + 1; j++)
				cur = (cur + C[i][j] * tree[u][j - 1] % MOD * tmp[i - j + 1] % MOD) % MOD;
			tree[u][i] = cur % MOD;
		}
		add[u] += num;
		return;
	}
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lc, num);
	if (r > mid) modify(l, r, mid + 1, t, rc, num);
	pushup(u);
	return;
}

void assign(int l, int r, int s, int t, int u, ll num) {
	if (l <= s && t <= r) {
		tmp[0] = 1;
		for (int i = 1; i <= 10; i++) tmp[i] = (tmp[i - 1] * num) % MOD;
		for (int i = 0; i <= 10; i++) tree[u][i] = ((t - s + 1) * tmp[i]) % MOD;
		add[u] = 0, ass[u] = num;
		return;
	}
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) assign(l, r, s, mid, lc, num);
	if (r > mid) assign(l, r, mid + 1, t, rc, num);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u, int k) {
	if (l <= s && t <= r) return tree[u][k] % MOD;
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	ll res = 0;
	pushdown(s, t, u);
	if (l <= mid) res = (res + query(l, r, s, mid, lc, k)) % MOD;
	if (r > mid) res = (res + query(l, r, mid + 1, t, rc, k)) % MOD;
	return res;
}

int main() {
	// freopen("ink.in", "r", stdin);
	// freopen("ink.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	getC();

	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	build(1, n, 1);

	while (m--) {
		cin >> opt >> l >> r >> x;
		if (opt == 1) modify(l, r, 1, n, 1, x);
		else if (opt == 2) assign(l, r, 1, n, 1, x);
		else cout << query(l, r, 1, n, 1, x) << endl;
	}
	return 0;
}