#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 50;
int n, m;
int st[N << 2], ed[N << 2];

inline void pushup(int u) {
	return (void)(st[u] = st[u << 1] + st[u << 1 | 1], ed[u] = ed[u << 1] + ed[u << 1 | 1]);
}

void updateStart(int target, int s, int t, int u) {
	if (s == target && t == target) return (void)(st[u]++);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (target <= mid) updateStart(target, s, mid, lc);
	else updateStart(target, mid + 1, t, rc);
	pushup(u);
	return; 
}

void updateEnd(int target, int s, int t, int u) {
	if (s == target && t == target) return (void)(ed[u]++);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (target <= mid) updateEnd(target, s, mid, lc);
	else updateEnd(target, mid + 1, t, rc);
	pushup(u);
	return; 
}

int queryStart(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return st[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	if (l <= mid) res += queryStart(l, r, s, mid, lc);
	if (r > mid) res += queryStart(l, r, mid + 1, t, rc);
	return res;
}

int queryEnd(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return ed[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	if (l <= mid) res += queryEnd(l, r, s, mid, lc);
	if (r > mid) res += queryEnd(l, r, mid + 1, t, rc);
	return res;
}

void update(int x, int y) {
	return (void)(updateStart(x, 1, n, 1), updateEnd(y, 1, n, 1));
}

int query(int x, int y) {
	return queryStart(1, y, 1, n, 1) - queryEnd(1, x - 1, 1, n, 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	while (m--) {
		int opt, x, y;
		cin >> opt >> x >> y;
		if (opt == 1) update(x, y);
		else cout << query(x, y) << endl;
	}
	return 0;
}