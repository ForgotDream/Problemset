#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;
ll n, m, seed, vmax;

struct Node {
	ll l, r;
	mutable ll val;
	Node(ll l, ll r, ll v) : l(l), r(r), val(v) {}
	bool operator< (const Node& oth) const {
		return l < oth.l;
	}
};
set<Node> tree;

inline ll fastPow(ll base, ll time, ll mod) {
	ll res = 1;
	base %= mod;
	while (time) {
		if (time & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		time >>= 1;
	}
	return res % mod;
}

inline auto split(ll pos) {
	auto it = tree.lower_bound(Node(pos, 0, 0));
	if (it != tree.end() && it->l == pos) return it;
	it--;
	ll l = it->l, r = it->r, val = it->val;
	tree.erase(it);
	tree.insert(Node(l, pos - 1, val));
	return tree.insert(Node(pos, r, val)).first;
}

inline void assign(ll l, ll r, ll num) {
	auto end = split(r + 1), begin = split(l);
	tree.erase(begin, end);
	tree.insert(Node(l, r, num));
	return;
}

inline void add(ll l, ll r, ll num) {
	auto end = split(r + 1), begin = split(l);
	for (auto it = begin; it != end; it++) it->val += num;
	return;
}

inline ll getKthNum(ll l, ll r, ll k) {
	vector<pair<ll, ll>> sorting;
	auto end = split(r + 1), begin = split(l);
	for (auto it = begin; it != end; it++)
		sorting.emplace_back(it->val, it->r - it->l + 1);
	sort(sorting.begin(), sorting.end());
	int pivot = 0;
	for (auto p : sorting) {
		k -= p.second;
		if (k <= 0) return p.first;
	}
	return -1;
}

inline ll getPowSum(ll l, ll r, ll k, ll mod) {
	auto end = split(r + 1), begin = split(l);
	ll res = 0;
	for (auto it = begin; it != end; it++) 
		res = (res + (it->r - it->l + 1) * fastPow(it->val, k, mod) % mod) % mod;
	return res % mod;
}

ll rnd() {
	ll res = seed;
	seed = (seed * 7 + 13) % MOD;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> seed >> vmax;
	for (int i = 1; i <= n; i++) tree.insert(Node(i, i, rnd() % vmax + 1));
	while (m--) {
		ll opt = (rnd() % 4) + 1, l = (rnd() % n) + 1, r = (rnd() % n) + 1, x, y;
		if (l > r) swap(l, r);
		if (opt == 3) x = (rnd() % (r - l + 1)) + 1;
		else x = (rnd() % vmax) + 1;
		if (opt == 1) add(l, r, x);
		else if (opt == 2) assign(l, r, x);
		else if (opt == 3) cout << getKthNum(l, r, x) << endl;
		else if (opt == 4) y = (rnd() % vmax) + 1, cout << getPowSum(l, r, x, y) << endl;
	}
	return 0;
}