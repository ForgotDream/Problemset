#include <bits/stdc++.h>

using namespace std;

#define int long long
#define i64 long long
#define ull unsigned long long
#define ldb long double
#define db double
#define i128 __int128
#define up(a, b, c) for (int a = (b); a <= (c); a++)
#define dn(a, b, c) for (int a = (b); a >= (c); a--)
#define pii pair<int, int>
#define pivi pair<int, vector<int> >
#define lc k << 1
#define rc k << 1 | 1
#define fi first
#define se second
#define endl '\n'
#define i16 short
#define eps 1e-8

const int N = 1e5 + 100, M = 2e6 + 100;
const int mod = 998244853;
const int inf = 1e9 + 7;
const ull uinf = 1e18 + 14;

namespace IO {
inline int read() {
  char c = getchar();
  int x = 0, fh = 0;
  while (c < '0' || c > '9') {
    fh |= c == '-';
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = getchar();
  }
  return fh ? -x : x;
}
inline void wt(int x) {
  if (x < 0) {
    x = -x;
    putchar('-');
  }
  if (x > 9) wt(x / 10);
  putchar((x % 10) ^ 48);
}
inline void write(int x, bool op) {
  wt(x);
  putchar(op ? '\n' : ' ');
}
}  // namespace IO
using namespace IO;
int n, m;
int a[N];
struct SegmentTree {
  struct node {
    int l, r, tag1, tag2;
    int lmax1, rmax1, ans1, sum1;
    int lmax0, rmax0, ans0, sum0;
  } tr[N << 2];
  inline void push_up(int k) {
    if (tr[lc].lmax1 == tr[lc].r - tr[lc].l + 1)
      tr[k].lmax1 = tr[rc].lmax1 + tr[lc].lmax1;
    else
      tr[k].lmax1 = tr[lc].lmax1;
    if (tr[lc].lmax0 == tr[lc].r - tr[lc].l + 1)
      tr[k].lmax0 = tr[rc].lmax0 + tr[lc].lmax0;
    else
      tr[k].lmax0 = tr[lc].lmax0;
    if (tr[rc].rmax1 == tr[rc].r - tr[rc].l + 1)
      tr[k].rmax1 = tr[rc].rmax1 + tr[lc].rmax1;
    else
      tr[k].rmax1 = tr[rc].rmax1;
    if (tr[rc].rmax0 == tr[rc].r - tr[rc].l + 1)
      tr[k].rmax0 = tr[rc].rmax0 + tr[lc].rmax0;
    else
      tr[k].rmax0 = tr[rc].rmax0;
    tr[k].ans1 = max({tr[lc].rmax1 + tr[rc].lmax1, tr[lc].ans1, tr[rc].ans1});
    tr[k].ans0 = max({tr[lc].rmax0 + tr[rc].lmax0, tr[lc].ans0, tr[rc].ans0});
    tr[k].sum1 = tr[lc].sum1 + tr[rc].sum1;
    tr[k].sum0 = tr[k].r - tr[k].l + 1 - tr[k].sum1;
  }
  inline void build(int k = 1, int l = 1, int r = n) {
    tr[k].l = l;
    tr[k].r = r;
    if (l == r) {
      tr[k].lmax0 = tr[k].rmax0 = tr[k].ans0 = tr[k].sum0 = a[l] == 0;
      tr[k].lmax1 = tr[k].rmax1 = tr[k].ans1 = tr[k].sum1 = a[l] == 1;
      return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    push_up(k);
  }
  inline void push_down(int k) {
    if (tr[k].tag1 == 1) {
      tr[k].tag2 = 0;
      tr[lc].lmax1 = tr[lc].rmax1 = tr[lc].ans1 = tr[lc].sum1 =
          tr[lc].r - tr[lc].l + 1;
      tr[lc].lmax0 = tr[lc].rmax0 = tr[lc].ans0 = tr[lc].sum0 = 0;
      tr[rc].lmax1 = tr[rc].rmax1 = tr[rc].ans1 = tr[rc].sum1 =
          tr[rc].r - tr[rc].l + 1;
      tr[rc].lmax0 = tr[rc].rmax0 = tr[rc].ans0 = tr[rc].sum0 = 0;
      tr[lc].tag1 = tr[rc].tag1 = 1;
      tr[lc].tag2 = tr[rc].tag2 = 0;
      tr[k].tag1 = 0;
    }
    if (tr[k].tag1 == 2) {
      tr[k].tag2 = 0;
      tr[lc].lmax1 = tr[lc].rmax1 = tr[lc].ans1 = tr[lc].sum1 = 0;
      tr[lc].lmax0 = tr[lc].rmax0 = tr[lc].ans0 = tr[lc].sum0 =
          tr[lc].r - tr[lc].l + 1;
      tr[rc].lmax1 = tr[rc].rmax1 = tr[rc].ans1 = tr[rc].sum1 = 0;
      tr[rc].lmax0 = tr[rc].rmax0 = tr[rc].ans0 = tr[rc].sum0 =
          tr[rc].r - tr[rc].l + 1;
      tr[lc].tag1 = tr[rc].tag1 = 2;
      tr[lc].tag2 = tr[rc].tag2 = 0;
      tr[k].tag1 = 0;
    }
    if (tr[k].tag2) {
      if (tr[lc].tag1 != 0)
        tr[lc].tag1 = tr[lc].tag1 % 2 + 1;
      else
        tr[lc].tag2 ^= 1;
      if (tr[rc].tag1 != 0)
        tr[rc].tag1 = tr[rc].tag1 % 2 + 1;
      else
        tr[rc].tag2 ^= 1;
      swap(tr[lc].sum1, tr[lc].sum0);
      swap(tr[lc].lmax1, tr[lc].lmax0);
      swap(tr[lc].rmax1, tr[lc].rmax0);
      swap(tr[lc].ans1, tr[lc].ans0);
      swap(tr[rc].sum1, tr[rc].sum0);
      swap(tr[rc].lmax1, tr[rc].lmax0);
      swap(tr[rc].rmax1, tr[rc].rmax0);
      swap(tr[rc].ans1, tr[rc].ans0);
      tr[k].tag2 = 0;
    }
  }
  inline void change1(int k, int l, int r, int val) {
    if (tr[k].l >= l && tr[k].r <= r) {
      if (val == 1) {
        tr[k].lmax1 = tr[k].rmax1 = tr[k].ans1 = tr[k].sum1 =
            tr[k].r - tr[k].l + 1;
        tr[k].lmax0 = tr[k].rmax0 = tr[k].ans0 = tr[k].sum0 = 0;
      } else if (val == 2) {
        tr[k].lmax1 = tr[k].rmax1 = tr[k].ans1 = tr[k].sum1 = 0;
        tr[k].lmax0 = tr[k].rmax0 = tr[k].ans0 = tr[k].sum0 =
            tr[k].r - tr[k].l + 1;
      }
      tr[k].tag1 = val;
      // tr[k].tag2=0;
      return;
    }
    int mid = (tr[k].l + tr[k].r) >> 1;
    push_down(k);
    if (mid >= l) change1(lc, l, r, val);
    if (mid < r) change1(rc, l, r, val);
    push_up(k);
  }
  inline void change2(int k, int l, int r) {
    if (tr[k].l >= l && tr[k].r <= r) {
      swap(tr[k].lmax0, tr[k].lmax1);
      swap(tr[k].rmax0, tr[k].rmax1);
      swap(tr[k].ans0, tr[k].ans1);
      swap(tr[k].sum0, tr[k].sum1);
      tr[k].tag2 ^= 1;
      return;
    }
    int mid = (tr[k].l + tr[k].r) >> 1;
    push_down(k);
    if (mid >= l) change2(lc, l, r);
    if (mid < r) change2(rc, l, r);
    push_up(k);
  }
  inline int asksum(int k, int l, int r) {
    if (tr[k].l >= l && tr[k].r <= r) return tr[k].sum1;
    int mid = (tr[k].l + tr[k].r) >> 1, res = 0;
    push_down(k);
    if (mid >= l) res = res + asksum(lc, l, r);
    if (mid < r) res = res + asksum(rc, l, r);
    return res;
  }
  inline node askans(int k, int l, int r) {
    if (tr[k].l >= l && tr[k].r <= r) return tr[k];
    int mid = (tr[k].l + tr[k].r) >> 1;
    push_down(k);
    if (r <= mid) return askans(lc, l, r);
    if (l > mid) return askans(rc, l, r);
    node t1 = askans(lc, l, r), t2 = askans(rc, l, r), t3;
    if (t1.sum1 == t1.r - t1.l + 1)
      t3.lmax1 = t1.lmax1 + t2.lmax1;
    else
      t3.lmax1 = t1.lmax1;
    if (t1.sum0 == t1.r - t1.l + 1)
      t3.lmax0 = t1.lmax0 + t2.lmax0;
    else
      t3.lmax0 = t1.lmax0;
    if (t2.sum1 == t2.r - t2.l + 1)
      t3.rmax1 = t1.rmax1 + t2.rmax1;
    else
      t3.rmax1 = t2.rmax1;
    if (t2.sum0 == t2.r - t2.l + 1)
      t3.rmax0 = t1.rmax0 + t2.rmax0;
    else
      t3.rmax0 = t2.rmax0;
    t3.sum1 = t1.sum1 + t2.sum1;
    t3.sum0 = t1.sum0 + t2.sum0;
    t3.ans1 = max({t1.ans1, t2.ans1, t1.rmax1 + t2.lmax1});
    t3.ans0 = max({t1.ans0, t2.ans0, t1.rmax0 + t2.lmax0});
    return t3;
  }
} T;
signed main() {
  n = read();
  m = read();
  up(i, 1, n) a[i] = read();
  T.build();
  int op, x, l, r;
  up(i, 1, m) {
    op = read();
    l = read() + 1;
    r = read() + 1;
    // cout<<l<<" "<<r<<endl;
    if (op == 0) T.change1(1, l, r, 2);
    if (op == 1) T.change1(1, l, r, 1);
    if (op == 2) T.change2(1, l, r);
    if (op == 3) write(T.asksum(1, l, r), 1);
    if (op == 4) write(T.askans(1, l, r).ans1, 1);
  }
  return 0;
}
