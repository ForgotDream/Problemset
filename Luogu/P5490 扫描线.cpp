#include <iostream>
#include <cstdio>
#include <algorithm>

const int N = 2e5 + 50; 
int n, cnt, y[N];
long long ans;

struct Node {
	int l, r, cover; 
	long long len;
} segt[N << 3];

struct Line {
	int x, y1, y2;
	int d;
	bool operator< (const Line& oth) const {
		return x < oth.x;
	}
} line[N];

inline void pushup(int u) {
	int lc = 2 * u, rc = 2 * u + 1;
	if (segt[u].cover) segt[u].len = segt[u].r - segt[u].l; 
	else segt[u].len = segt[lc].len + segt[rc].len;
	return;
}

void build(int l, int r, int u) {
	segt[u].l = y[l], segt[u].r = y[r];
	if (r - l <= 1) return;
	build(l, (l + r) / 2, 2 * u);
	build((l + r) / 2, r, 2 * u + 1);
	return;
}

void modify(int s, int t, int d, int u) {
	int l = segt[u].l, r = segt[u].r;
	if (s <= l && r <= t) {
		segt[u].cover += d;
		pushup(u);
		return;
	}
	int mid = (s + t) / 2, lc = 2 * u, rc = 2 * u + 1;
	if (s < segt[lc].r) modify(s, t, d, lc);
	if (t > segt[rc].l) modify(s, t, d, rc);
	pushup(u);
	return;
}

void solve() {
	std::sort(y + 1, y + cnt + 1);
	std::sort(line + 1, line + cnt + 1);
	build(1, cnt, 1);
	for (int i = 1; i <= cnt; i++) {
		ans += segt[1].len * (line[i].x - line[i - 1].x);
		modify(line[i].y1, line[i].y2, line[i].d, 1);
	}
	std::cout << ans << std::endl;
	return;
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		line[++cnt] = (Line){a, b, d, 1}, y[cnt] = b;
		line[++cnt] = (Line){c, b, d, -1}, y[cnt] = d;
	}
	solve();
	return 0;
}