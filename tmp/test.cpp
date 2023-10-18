#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e5 + 5;
struct Tree {
#define ls(k) (k << 1)
#define rs(k) (k << 1 | 1)
  int t[MAXN << 2], tg[MAXN << 2];
  Tree() {
    memset(t, 0, sizeof t);
    memset(tg, 0, sizeof tg);
  }
  void pu(int k) { t[k] = min(t[ls(k)], t[rs(k)]); }
  void pd(int k) {
    if (!tg[k]) return;
    t[ls(k)] += tg[k];
    t[rs(k)] += tg[k];
    tg[ls(k)] += tg[k];
    tg[rs(k)] += tg[k];
    tg[k] = 0;
  }
  void upd(int le, int ri, int k, int l, int r, int x) {
    if (le <= l && r <= ri) {
      tg[k] += x;
      t[k] += x;
      return;
    }
    int mid = l + r >> 1;
    pd(k);
    if (le <= mid) upd(le, ri, ls(k), l, mid, x);
    if (ri > mid) upd(le, ri, rs(k), mid + 1, r, x);
    pu(k);
  }
  int que(int le, int ri, int k, int l, int r) {
    if (le <= l && r <= ri) return t[k];
    int mid = l + r >> 1, ans = 1e9;
    pd(k);
    if (le <= mid) ans = min(ans, que(le, ri, ls(k), l, mid));
    if (ri > mid) ans = min(ans, que(le, ri, rs(k), mid + 1, r));
    return ans;
  }
} T;
struct node {
  int s, p, opt;
  bool operator<(const node &x) const {
    return s != x.s ? s < x.s : opt < x.opt;
  }
} A[MAXN];
int n;
stack<int> st[MAXN];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int p, s;
    scanf("%d %d", &p, &s);
    A[i] = node{s, p, 0};
  }
  for (int i = 1; i <= n; ++i) {
    int p, s;
    scanf("%d %d", &p, &s);
    A[i + n] = node{s, p, 1};
  }
  n *= 2;
  sort(A + 1, A + 1 + n);
  int ans = n / 2;
  for (int i = 1; i <= n; ++i) {
    if (A[i].opt == 0) {
      st[A[i].p].push(i);
      T.upd(i, n, 1, 1, n, 1);
    } else {
      if (st[A[i].p].empty()) {
        T.upd(i, n, 1, 1, n, -1);
        continue;
      }
      int p = st[A[i].p].top();
      T.upd(p, n, 1, 1, n, -1);
      if (T.que(1, i, 1, 1, n) < 0) {
        T.upd(p, n, 1, 1, n, 1);
        T.upd(i, n, 1, 1, n, -1);
      } else
        ans--, st[A[i].p].pop();
    }
  }
  printf("%d\n", ans);
  return 0;
}
