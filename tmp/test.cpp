#include <bits/stdc++.h>
#define rap(i, s, n) for (int i = s; i <= n; i++)
#define drap(i, n, s) for (int i = n; i >= s; i--)
#define N 5111
#define Q 100000000
#define ll long long
#define m(s, k) memset(s, k, sizeof s)
char xA[1 << 16], xZ[20];
int xC = -1, xzz = 0;
inline void wt_z() { fwrite(xA, 1, xC + 1, stdout), xC = -1; }
template <class T>
inline void wt(T x, int t) {
  if (xC > (1 << 15)) wt_z();
  while (xZ[++xzz] = (char)(x % 10 + '0'), (x /= 10) || (t > 0)) --t;
  while (xA[++xC] = xZ[xzz], --xzz);
}
// 得益于luogu的代码公开计划我可以愉快地抄大佬的快输板子了（不算抄袭吧QAQ）
using namespace std;
ll res[N], a[N], d[N];
int sz1, sz2;
int cheng(ll *a, int n, ll *b, int m) {
  m(d, 0);
  rap(i, 0, n) rap(j, 0, m) d[i + j] += a[i] * b[j];
  rap(i, 0, n + m) d[i + 1] += d[i] / Q, d[i] %= Q;
  int t = n + m + 1;
  while (d[t]) d[t + 1] += d[t] / Q, d[t] %= Q, t++;
  t--;
  rap(i, 0, t) a[i] = d[i];
  return t;
}
// 非常暴力又写的不是一般难看的乘
int main() {
  int n, m;
  scanf("%d", &m);
  rap(i, 1, m) {
    scanf("%d", &n);
    int t = n + 1;
    m(res, 0);
    res[0] = 1;
    m(a, 0);
    a[0] = 2;
    sz1 = sz2 = 0;
    while (t) {
      if (t & 1) sz1 = cheng(res, sz1, a, sz2);
      t >>= 1;
      if (t) sz2 = cheng(a, sz2, a, sz2);
    }
    if (n & 1) res[0]++;
    res[0] -= 2;
    if (res[0] < 0) res[0] += Q, res[1]--;
    ll k = 0;
    drap(i, sz1, 0) {
      k = k * Q + res[i];
      res[i] = k / 3;
      k %= 3;
    }
    while (res[sz1] == 0) sz1--;
    wt(res[sz1], 0);
    drap(i, sz1 - 1, 0) wt(res[i], 7);
    xA[++xC] = '\n';
    wt_z();
  }
  return 0;
}
