/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

constexpr int N = 1.2e4 + 50, Q = 1e6 + 50;
int n, q;
i64 X[N], Y[N];

// atan2(double y, double x): 返回 atan(y / x)，也就是极角
// 可用于按斜率排序，但是这题好像不需要！

struct Query {
  i64 z, r;
  int idx;
  bool operator<(const Query &rhs) const {
    return z < rhs.z;
  }
} qry[Q];

int blk, bcnt, lp[N], rp[N];

struct Line {
  i64 k, b;
  int idx;
  i64 operator()(i64 x) { return k * x + b; }
  bool operator<(const Line &rhs) const {
    return k > rhs.k || (k == rhs.k && b < rhs.b);
  }
} line[N];
int lcnt;

int ans[Q];
struct Event {
  int u, v;
  double w;
  inline i64 up() const { return line[u].b - line[v].b; }
  inline i64 dn() const { return line[u].k - line[v].k; }
  bool operator<(const Event &rhs) const {
    if (i128(up()) * rhs.dn() == i128(dn()) * rhs.up()) {
      if (line[u].k == line[rhs.u].k) return line[v].k > line[rhs.v].k;
      else return line[u].k > line[rhs.u].k;
    } else {
      return w < rhs.w;
    }
  }
} event[Q];
int ecnt;

int p[N];

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> X[i] >> Y[i];

  for (int i = 1; i <= q; i++) {
    auto &[z, r, idx] = qry[i];
    std::cin >> z >> r, idx = i, r = r * r - z * z;
  }
  std::sort(qry + 1, qry + q + 1);

  blk = std::sqrt(q), bcnt = (n - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;
  rp[bcnt] = n;

  for (int i = 1; i <= bcnt; i++) {
    lcnt = 0;
    for (int j = lp[i]; j <= rp[i]; j++) {
      line[++lcnt] = {-2 * Y[j], X[j] * X[j] + Y[j] * Y[j], j - lp[i] + 1};
    }

    ecnt = 0;
    for (int j = 1; j <= lcnt; j++) {
      for (int k = j + 1; k <= lcnt; k++) {
        if (line[j].k == line[k].k) continue;  // 斜率不存在！
        double w = double(line[j].b - line[k].b) / (line[k].k - line[j].k);
        event[++ecnt] = {j, k, w};
        if (line[j].k < line[k].k) std::swap(event[ecnt].u, event[ecnt].v);
      }
    }

    std::sort(line + 1, line + lcnt + 1);
    std::sort(event + 1, event + ecnt + 1);
    for (int j = 1; j <= lcnt; j++) p[line[j].idx] = j;

    int piv = 1;
    for (int j = 1; j <= q; j++) {
      while (piv <= ecnt && event[piv].w <= qry[j].z) {
        // std::swap(line[p[event[piv].u]], line[p[event[piv].v]]);
        // std::swap(p[event[piv].u], p[event[piv].v]);
        if (p[event[piv].u] < p[event[piv].v]) {
          std::swap(line[p[event[piv].u]], line[p[event[piv].v]]);
          std::swap(p[event[piv].u], p[event[piv].v]);
        }
        piv++;
      }
      int lo = 1, hi = lcnt, cur = 0;
      while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (line[mid](qry[j].z) <= qry[j].r) lo = mid + 1, cur = mid;
        else hi = mid - 1;
      }
      ans[qry[j].idx] += cur;
    }
  }

  for (int i = 1; i <= q; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
