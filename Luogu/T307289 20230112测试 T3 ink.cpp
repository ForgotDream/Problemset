#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;
int n, m;
int opt, l, r;
ll x;
struct Node {
	int l, r;
	mutable ll val;
	Node (int l, int r, ll v) : l(l), r(r), val(v) {}
	bool operator< (const Node& oth) const {
		return l < oth.l;
	}
};
set<Node> tree;

ll fastPow(ll base, int time) {
	ll res = 1;
	base %= MOD;
	while (time) {
		if (time & 1) res = (res * base) % MOD;
		base = (base * base) % MOD;
		time >>= 1;
	}
	return res % MOD;
}

auto split(int pos) {
	auto it = tree.lower_bound(Node(pos, 0, 0));
	if (it != tree.end() && it->l == pos) return it;
	it--;
	int l = it->l, r = it->r;
	ll val = it->val;
	tree.erase(it), tree.insert(Node(l, pos - 1, val));
	return tree.insert(Node(pos, r, val)).first;
}

void assign(int l, int r, ll val) {
	auto end = split(r + 1), begin = split(l);
	tree.erase(begin, end);
	tree.insert(Node(l, r, val));
	return;
}

void add(int l, int r, ll val) {
	auto end = split(r + 1), begin = split(l);
	for (auto it = begin; it != end; it++) it->val = (it->val + val) % MOD;
	return;
}

ll query(int l, int r, int k) {
	ll res = 0;
	auto end = split(r + 1), begin = split(l);
	for (auto it = begin; it != end; it++) 
		res = (res + (fastPow(it->val, k)) * (it->r - it->l + 1) % MOD) % MOD;
	return res % MOD;
}

void solve() {
	while (m--) {
		cin >> opt >> l >> r >> x;
		if (opt == 1) add(l, r, x);
		else if (opt == 2) assign(l, r, x);
		else cout << query(l, r, x) << endl;
	}
	return;
}

int main() {
	// freopen("ink1.in", "r", stdin);
	// freopen("ink.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, w; i <= n; i++) cin >> w, tree.insert(Node(i, i, w));
	solve();
	return 0;
}