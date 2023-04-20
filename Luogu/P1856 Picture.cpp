#include <bits/stdc++.h>

namespace FastIO{
	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 2e4 + 50;
// Part of ScanLine
int n, cnt, maxx = -1e9, minn = 1e9;
struct Line {
	int l, r, h, delta;
	Line() {};
	Line(int l, int r, int h, int d) : l(l), r(r), h(h), delta(d) {}
	// Attetion! If two segments' height are the same, compare them by thier delta, which means the segment is a in or out segment;
	/* Hack:
	 * In:		Out: 24
	 * 2
	 * 0 0 4 4
	 * 0 4 4 8
	 */
	bool operator< (const Line &oth) const {
		if (h != oth.h) return h < oth.h;
		else return delta > oth.delta;
	}
} line[N << 3];
int ans, lst;
// Part of segment Tree
int lflag[N << 3], rflag[N << 3];
int num[N << 3], isValid[N << 3], length[N << 3];

inline void pushup(int l, int r, int u) {
	int lc = u << 1, rc = u << 1 | 1;
	// Three possible situation:
	if (isValid[u]) lflag[u] = rflag[u] = true, length[u] = r - l + 1, num[u] = 1;   // 1. This segment is valid
	else if (l == r) lflag[u] = rflag[u] = false, length[u] = num[u] = 0;   // 2. This node is leaf
	else lflag[u] = lflag[lc], rflag[u] = rflag[rc], length[u] = length[lc] + length[rc], num[u] = num[lc] + num[rc] - (lflag[rc] && rflag[lc]);
	// 3. Other situation, calculate from child node
	return;
}

void update(int l, int r, int s, int t, int u, int delta) {   // common update
	if (l <= s && t <= r) return (void)(isValid[u] += delta, pushup(s, t, u));
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (l <= mid) update(l, r, s, mid, lc, delta);
	if (r > mid) update(l, r, mid + 1, t, rc, delta);
	pushup(s, t, u);
	return;
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		int x1, x2, y1, y2;
		read(x1, y1, x2, y2);
		maxx = max(maxx, x2), minn = min(minn, x1);
		line[++cnt] = Line(x1, x2, y1, 1), line[++cnt] = Line(x1, x2, y2, -1);
	}
	// cerr << maxx << ' ' << minn << endl;
	stable_sort(line + 1, line + cnt + 1);   // sort by height of scanline
	for (int i = 1; i <= cnt; i++) {
		if (line[i].l <= line[i].r) update(line[i].l, line[i].r - 1, minn, maxx - 1, 1, line[i].delta);
		ans += 2 * num[1] * (line[i + 1].h - line[i].h);
		ans += abs(length[1] - lst), lst = length[1];   // lst means the length of the previous interval
	}
	print(ans, '\n');
	return 0;
}