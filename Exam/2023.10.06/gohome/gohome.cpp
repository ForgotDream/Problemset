#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, a[N];
std::vector<int> b;
struct SegTree {
  i64 sum[N << 2], cnt[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) {
    sum[u] = sum[lc(u)] + sum[rc(u)], cnt[u] = cnt[lc(u)] + cnt[rc(u)];
  }
  void clear() {
    std::memset(sum, 0, sizeof(sum)), std::memset(cnt, 0, sizeof(cnt));
  }
  void modify(int tar, int s, int t, int u) {
    if (s == t) return cnt[u]++, sum[u] += b[s - 1], void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
    pushup(u);
  }
  int query(int s, int t, int u, i64 val) {
    if (s == t) return std::min(cnt[u], val / b[s - 1]);
    int mid = (s + t) >> 1;
    if (val < sum[lc(u)]) return query(s, mid, lc(u), val);
    else return cnt[lc(u)] + query(mid + 1, t, rc(u), val - sum[lc(u)]);
  }
} seg;
void solve() {
  std::cin >> n >> m;
  b.clear(), seg.clear();
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; i++) {
    int ans = i - seg.query(1, b.size(), 1, m - a[i]) - 1;
    std::cout << ans << " \n"[i == n];
    int k = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    seg.modify(k, 1, b.size(), 1);
  }
}

int main() {
  std::freopen("gohome.in", "r", stdin);
  std::freopen("gohome.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
