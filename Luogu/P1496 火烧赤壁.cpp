/**
 * @file    P1496 火烧赤壁.cpp
 * @author  ForgotDream
 * @brief   模拟 / ODT
 * @date    2023-02-04
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 2e4 + 50;
struct Node {
	i64 l, r;
	mutable i64 val;
	Node(i64 l, i64 r, i64 v) : l(l), r(r), val(v) {}
	bool operator< (const Node& oth) const {
		return l < oth.l;
	}
};
set<Node> tree;
int n, ans;

inline auto split(i64 pos) {
	auto it = tree.lower_bound(Node(pos, 0, 0));
	if (it != tree.end() && it->l == pos) return it;
	it--;
	i64 l = it->l, r = it->r, val = it->val;
	tree.erase(it);
	tree.insert(Node(l, pos - 1, val));
	return tree.insert(Node(pos, r, val)).first;
}

inline void assign(i64 l, i64 r, i64 num) {
	auto end = split(r + 1), begin = split(l);
	tree.erase(begin, end);
	tree.insert(Node(l, r, num));
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	tree.insert({-(1ll << 31), 1ll << 31, 0});

	cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
		assign(x, y - 1, 1);
	}

	for (auto it = tree.begin(); it != tree.end(); it++) {
		ans += it->val * (it->r - it->l + 1);
	}

	cout << ans << '\n';
	return 0;
}