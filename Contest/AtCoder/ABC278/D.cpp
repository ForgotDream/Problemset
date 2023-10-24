#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;
const ll MAXN = 200005;

struct Node {
	ll l, r;
	mutable ll v;

	Node(ll l, ll r = 0, ll v = 0) : l(l), r(r), v(v) {}

	bool operator<(const Node &a) const {
		return l < a.l;
	}
};

ll n, m, seed, vmax, a[MAXN];
set<Node> s;

set<Node>::iterator split(int pos) {
	set<Node>::iterator it = s.lower_bound(Node(pos));
	if (it != s.end() && it->l == pos) {
		return it;
	}
	it--;
	if (it->r < pos) return s.end();
	ll l = it->l;
	ll r = it->r;
	ll v = it->v;
	s.erase(it);
	s.insert(Node(l, pos - 1, v));
	return s.insert(Node(pos, r, v)).first;
}

void add(ll l, ll r, ll x) {
	set<Node>::iterator itr = split(r + 1), itl = split(l);
	for (set<Node>::iterator it = itl; it != itr; ++it) {
		it->v += x;
	}
}

void assign(ll l, ll r, ll x) {
	set<Node>::iterator itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(Node(l, r, x));
}

struct Rank {
	ll num, cnt;

	bool operator<(const Rank &a) const {
		return num < a.num;
	}

	Rank(ll num, ll cnt) : num(num), cnt(cnt) {}
};

ll rnk(ll l, ll r, ll x) {
	set<Node>::iterator itr = split(r + 1), itl = split(l);
	vector<Rank> v;
	for (set<Node>::iterator i = itl; i != itr; ++i) {
		v.push_back(Rank(i->v, i->r - i->l + 1));
	}
	sort(v.begin(), v.end());
	int i;
	for (i = 0; i < v.size(); ++i) {
		if (v[i].cnt < x) {
			x -= v[i].cnt;
		} else {
			break;
		}
	}
	return v[i].num;
}

ll ksm(ll x, ll y, ll p) {
	ll r = 1;
	ll base = x % p;
	while (y) {
		if (y & 1) {
			r = r * base % p;
		}
		base = base * base % p;
		y >>= 1;
	}
	return r;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		s.insert(Node(i, i, a[i]));
	}
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		ll op, l, r, x, y;
		cin >> op;
		if (op == 1) {
			cin >> x;
			assign(1, n, x);
		} else if (op == 2) {
			cin >> l >> x;
			add(l, l, x);
		} else if (op == 3) {
			cin >> l;
			cout << rnk(l, l, 1) << endl;
		}
	}
	return 0;
}
