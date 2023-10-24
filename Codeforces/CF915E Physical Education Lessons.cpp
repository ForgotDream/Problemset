#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

const ll MOD = 1e9 + 7;
int ans, n, m;
struct Node {
	int l, r;
	mutable int val;
	Node(int l, int r, int v) : l(l), r(r), val(v) {}
	bool operator< (const Node& oth) const {
		return l < oth.l;
	}
};
set<Node> tree;

inline auto split(int pos) {
	auto it = tree.lower_bound(Node(pos, 0, 0));
	if (it != tree.end() && it->l == pos) return it;
	it--;
	int l = it->l, r = it->r, val = it->val;
	tree.erase(it);
	tree.insert(Node(l, pos - 1, val));
	return tree.insert(Node(pos, r, val)).first;
}

inline void assign(int l, int r, int opt) {
	auto end = split(r + 1), begin = split(l);
	int len = 0, tot = 0;
	for (auto it = begin; it != end; it++) {
		len += it->r - it->l + 1, tot += it->val * (it->r - it->l + 1);
	}
	tree.erase(begin, end);
	tree.insert(Node(l, r, opt));
	if (opt == 1) ans += (len - tot);
	else ans -= tot;
	return;
}

int main() {
	read(n, m);
	tree.insert(Node(1, n, 1));
	ans = n;
	while (m--) {
		int l, r, opt;
		read(l, r, opt);
		assign(l, r, opt == 1 ? 0 : 1);
		print(ans, '\n');
	}
	return 0;
}