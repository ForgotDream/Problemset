#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 d[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };

void solve() {
  int a, b, c;
  i64 k;
  std::cin >> a >> b >> c >> k;
  if (c < a || c < b) {
    std::cout << -1 << "\n";
    return;
  }
  i64 cnt = 0;
  for (int i = d[a - 1]; i < d[a]; i++) {
    i64 min = std::max(d[c - 1] - i, d[b - 1]);
    if (min >= d[b])  { continue; }
    i64 cur = std::min(d[b] - 1, (d[c] - 1) - i) - min + 1;
    // std::cerr << cur << " " << min << "\n";
    if (cnt + cur >= k) {
      std::cout << i << " + " << min + k - cnt - 1 
                << " = " << i + min + k - cnt - 1 << "\n";
      return;
    }
    cnt += cur;
  }
  std::cout << -1 << "\n";
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}
