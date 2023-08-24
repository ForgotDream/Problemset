#include <iostream>
#include <cstring>

using i64 = long long;

constexpr int N = 3e5 + 50;
int t, n, h[N];
i64 f[N], g[N], s1[N], s2[N], z1[N], z2[N];

template<int N = 1000050>
struct BIT {
  int tree[N];
  void clear() { std::memset(tree, 0, sizeof(tree)); }
  void add(int pos, int val) {
    for (int i = pos; i < N; i += (i & -i)) tree[i] += val;
  }
  int query(int pos) {
    int res = 0;
    for (int i = pos; i; i -= (i & -i)) res += tree[i];
    return res;
  }
};
BIT l, r;

void solve() {
  l.clear(), r.clear();

  std::cin >> n;
  for (int i = 0; i <= n + 1; i++) {
    f[i] = g[i] = s1[i] = s2[i] = z1[i] = z2[i] = 0;
  }

  for (int i = 1; i <= n; i++) std::cin >> h[i];
  
  for (int i = 1; i <= n; i++) s1[i] = s1[i - 1] + h[i];
  for (int i = n; i >= 1; i--) s2[i] = s2[i + 1] + h[i];

  for (int i = 1; i <= n; i++) {
    if (h[i - 1] >= h[i]) {
      i64 d = h[i - 1] - h[i] + 1;
      z1[i] = l.query(h[i] - 1);
      f[i] = std::min(s1[i - 1], f[i - 1] + (i - 1 - z1[i] + z1[i - 1]) * d);
    } else {
      f[i] = f[i - 1], z1[i] = z1[i - 1];
    }
    l.add(h[i], 1);
  }
  for (int i = n; i >= 1; i--) {
    if (h[i + 1] >= h[i]) {
      i64 d = h[i + 1] - h[i] + 1;
      z2[i] = r.query(h[i] - 1);
      g[i] = std::min(s2[i + 1], g[i + 1] + (n - i - z2[i] + z2[i + 1]) * d);
    } else {
      g[i] = g[i + 1], z2[i] = z2[i + 1];
    }
    r.add(h[i], 1);
  }

  std::cerr << "OK\n";
  
  i64 ans = 1e18;
  for (int i = 1; i <= n; i++) ans = std::min(ans, f[i] + g[i] + h[i]);
  std::cout << ans << "\n";

  for (int i = 1; i <= n; i++) std::cerr << z1[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) std::cerr << z2[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) std::cerr << f[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) std::cerr << g[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) std::cerr << h[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) std::cerr << f[i] + g[i] + h[i] << " \n"[i == n];
  std::cerr << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}