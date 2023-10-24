#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstdlib>
#define int long long

using namespace std;
using ll = long long;

const int N = 2e5 + 50;
int k, m, n;
ll a[N], sum, pre, tmp;

struct treap {  // 直接维护成数据结构，可以直接用
	int l[N], r[N], val[N], rnd[N], size[N], w[N];
	int sz, ans, rt;

	inline void pushup(int x) { size[x] = size[l[x]] + size[r[x]] + w[x]; }

	void lrotate(int &k) {
		int t = r[k];
		r[k] = l[t];
		l[t] = k;
		size[t] = size[k];
		pushup(k);
		k = t;
	}

	void rrotate(int &k) {
		int t = l[k];
		l[k] = r[t];
		r[t] = k;
		size[t] = size[k];
		pushup(k);
		k = t;
	}

	void insert(int &k, int x) {  // 插入
		if (!k) {
			sz++;
			k = sz;
			size[k] = 1;
			w[k] = 1;
			val[k] = x;
			rnd[k] = rand();
			return;
		}
		size[k]++;
		if (val[k] == x) {
			w[k]++;
		} else if (val[k] < x) {
			insert(r[k], x);
			if (rnd[r[k]] < rnd[k]) lrotate(k);
		} else {
			insert(l[k], x);
			if (rnd[l[k]] < rnd[k]) rrotate(k);
		}
	}

	bool del(int &k, int x) {  // 删除节点
		if (!k) return false;
		if (val[k] == x) {
			if (w[k] > 1) {
				w[k]--;
				size[k]--;
				return true;
			}
			if (l[k] == 0 || r[k] == 0) {
				k = l[k] + r[k];
				return true;
			} else if (rnd[l[k]] < rnd[r[k]]) {
				rrotate(k);
				return del(k, x);
			} else {
				lrotate(k);
				return del(k, x);
			}
		} else if (val[k] < x) {
			bool succ = del(r[k], x);
			if (succ) size[k]--;
			return succ;
		} else {
			bool succ = del(l[k], x);
			if (succ) size[k]--;
			return succ;
		}
	}

	int queryrank(int k, int x) {
		if (!k) return 0;
		if (val[k] == x)
			return size[l[k]] + 1;
		else if (x > val[k]) {
			return size[l[k]] + w[k] + queryrank(r[k], x);
		} else
			return queryrank(l[k], x);
	}

	int querynum(int k, int x) {
		if (!k) return 0;
		if (x <= size[l[k]])
			return querynum(l[k], x);
		else if (x > size[l[k]] + w[k])
			return querynum(r[k], x - size[l[k]] - w[k]);
		else
			return val[k];
	}
} T;

signed main() {
	srand(19260817);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	
	for (int i = 1; i <= n; i++) {
		// cout << sum << endl;
		int pre = T.querynum(T.rt, k);
		// cout << pre << endl;
		T.insert(T.rt, a[i]);
		// cout << (-T.querynum(T.rt, k - 1)) << endl;
		if (i <= k) sum += a[i];
		else {
			if (pre > a[i]) sum -= pre, sum += a[i];
		}
		if (i >= m) {
			int tmp = T.querynum(T.rt, k);
			T.del(T.rt, a[i - m + 1]);
			cout << sum << ' ';
			if (a[i - m + 1] <= tmp) sum -= a[i - m + 1], sum += T.querynum(T.rt, k);
			// if (a[i] <= pre) sum += a[i], sum -= pre;
		}
	}
	/*
	for (int i = 1; i <= n; i++) {
		T.insert(T.rt, a[i]), cout << T.querynum(T.rt, k) << endl;
		if (i >= m) T.del(T.rt, a[i - m + 1]);
	}
	*/
	return 0;
}