/**
 * @file    P5367 康托展开.cpp
 * @author  ForgotDream
 * @brief   康托展开
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e6 + 50, MOD = 998244353;
int n;
i64 fact[N], a[N];
struct FHQTreap {
	int val[N], prm[N], ch[N][2], size[N];
	int cnt, root;

	FHQTreap() { root = 0; };

	void init(int x) {
		val[++cnt] = x, prm[cnt] = rand();
		ch[cnt][0] = ch[cnt][1] = 0, size[cnt] = 1;
		return;
	} 

	void update(int u) {
		return (void)(size[u] = size[ch[u][0]] + size[ch[u][1]] + 1);
	}

	void split(int u, int x, int &l, int &r) {
		if (!u) return (void)(l = r = 0);
		if (val[u] <= x) l = u, split(ch[u][1], x, ch[u][1], r);
		else r = u, split(ch[u][0], x, l, ch[u][0]);
		update(u);
		return;
	}

	int merge(int l, int r) {
		if (!l || !r) 
			return l + r;
		if (prm[l] > prm[r]) 
			return ch[l][1] = merge(ch[l][1], r), update(l), l;
		else 
			return ch[r][0] = merge(l, ch[r][0]), update(r), r;
	}

	void insert(int x) {
		int l, r;
		split(root, x, l, r);
		init(x);
		root = merge(merge(l, cnt), r);
		return;
	}

	void del(int x) {
		int l, r, p;
		split(root, x, l, r);
		split(l, x - 1, l, p);
		p = merge(ch[p][0], ch[p][1]), root = merge(merge(l, p), r);
		return;
	}

	int getRankByNum(int x) {
		int l, r, tmp;
		split(root, x - 1, l, r);
		tmp = size[l] + 1;
		root = merge(l, r);
		return tmp;
	}

	int getNumByRank(int u, int x) {
		if (x == size[ch[u][0]] + 1) 
			return u;
		else if (x > size[ch[u][0]] + 1) 
			return getNumByRank(ch[u][1], x - size[ch[u][0]] - 1);
		else return getNumByRank(ch[u][0], x);
	}

	int getNumByRank(int x) {
		return val[getNumByRank(root, x)];
	}

	int getPrecursor(int x) {
		int l, r, tmp;
		split(root, x - 1, l, r);
		tmp = val[getNumByRank(l, size[l])];
		root = merge(l, r);
		return tmp;
	}

	int getSuccessor(int x) {
		int l, r, tmp;
		split(root, x, l, r);
		tmp = val[getNumByRank(r, 1)];
		root = merge(l, r);
		return tmp;
	}
} fhq;

i64 cantor() {
	i64 res = 0;
	for (int i = 1; i <= n; i++) {
		res = (res + (i64) (fhq.getRankByNum(a[i]) - 1) * fact[n - i] % MOD) % MOD;
		fhq.del(a[i]);
	}
	return (res + 1) % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], fhq.insert(a[i]);

	fact[0] = 1;
	for (int i = 1; i <= n; i++) fact[i] = (i64) (fact[i - 1] * i) % MOD;

	cout << cantor() << '\n';
	return 0;
}