/**
 * @file    CF762E Radio stations.cpp
 * @author  ForgotDream
 * @brief   CDQ
 * @date    2023-10-26
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k;
i64 ans;
std::vector<int> b;
struct Node {
  int x, y, z, s, t;
} p[N];
struct BIT {
  int tree[N * 5];
  void modify(int u, int val) {
    for (int i = u; i <= b.size(); i += (i & -i)) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= (i & -i)) res += tree[i];
    return res;
  }
} bit;
inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
bool cmp1(const Node &lhs, const Node &rhs) {
  if (lhs.y != rhs.y) return lhs.y > rhs.y;
  if (lhs.z != rhs.z) return lhs.z < rhs.z;
  return lhs.x < rhs.x;
}
bool cmp2(const Node &lhs, const Node &rhs) {
  if (lhs.z != rhs.z) return lhs.z < rhs.z;
  if (lhs.x != rhs.x) return lhs.x < rhs.x;
  return lhs.y > rhs.y;
}
void solve(int l, int r) {
  if (l >= r) return;
  int mid = (l + r) >> 1;
  solve(l, mid), solve(mid + 1, r);
  std::sort(p + l, p + mid + 1, cmp2), std::sort(p + mid + 1, p + r + 1, cmp2);
  int j1 = l, j2 = l - 1;
  for (int i = mid + 1; i <= r; i++) {
    while (j1 <= mid && p[i].z - p[j1].z > k) bit.modify(p[j1].x, -1), j1++;
    while (j2 < mid && p[j2 + 1].z - p[i].z <= k) j2++, bit.modify(p[j2].x, 1);
    ans += bit.query(p[i].t) - bit.query(p[i].s - 1);
  }
  for (int i = j1; i <= j2; i++) bit.modify(p[i].x, -1);
}
void solve() {
  std::cin >> n >> k;
  for (int i = 1, x, r, f; i <= n; i++) {
    std::cin >> x >> r >> f;
    p[i].x = x, p[i].y = r, p[i].z = f;
    p[i].s = std::max(0, x - r), p[i].t = x + r;
    b.push_back(x), b.push_back(p[i].s), b.push_back(p[i].t);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  for (int i = 1; i <= n; i++) {
    p[i].x = find(p[i].x), p[i].s = find(p[i].s), p[i].t = find(p[i].t);
  }
  std::sort(p + 1, p + n + 1, cmp1);
  solve(1, n);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
