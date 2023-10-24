/**
 * @file    P3810 【模板】三维偏序（陌上花开）.cpp
 * @author  ForgotDream
 * @brief   CDQ
 * @date    2023-07-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, K = 2e5 + 50;
int m, n, k, ans[N];
struct Node {
  int a, b, c, res, cnt;
} node[N], a[N];
struct BIT {
  int tree[K];
  void add(int u, int val) {
    for (int i = u; i <= k; i += i & -i) tree[i] += val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
} bit;

void solve(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  solve(l, mid), solve(mid + 1, r);
  auto cmp = [](const Node &lhs, const Node &rhs) {
    return lhs.b < rhs.b || (lhs.b == rhs.b && lhs.c < rhs.c);
  };
  std::sort(a + l, a + mid + 1, cmp);
  std::sort(a + mid + 1, a + r + 1, cmp);
  int i = l, j = mid + 1;
  while (j <= r) {
    while (i <= mid && a[i].b <= a[j].b) {
      bit.add(a[i].c, a[i].cnt), i++;
    }
    a[j].res += bit.query(a[j].c), j++;
  }
  for (int k = l; k < i; k++) bit.add(a[k].c, -a[k].cnt);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    std::cin >> node[i].a >> node[i].b >> node[i].c;
  }
  std::sort(node + 1, node + n + 1, [](auto lhs, auto rhs) {
              if (lhs.a != rhs.a) return lhs.a < rhs.a;
              if (lhs.b != rhs.b) return lhs.b < rhs.b;
              return lhs.c < rhs.c;
            });
  for (int i = 1; i <= n; i++) {
    if (i == 1 ||
        node[i].a != node[i - 1].a ||
        node[i].b != node[i - 1].b ||
        node[i].c != node[i - 1].c) {
      a[++m] = node[i], a[m].cnt = 1;
    } else {
      a[m].cnt++;
    }
  }
  solve(1, m);
  for (int i = 1; i <= m; i++) ans[a[i].res + a[i].cnt - 1] += a[i].cnt;
  for (int i = 0; i < n; i++) std::cout << ans[i] << "\n";

  return 0;
}