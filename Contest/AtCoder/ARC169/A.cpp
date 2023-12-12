#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2.5e5 + 50;
int n, p[N], dep[N];
i64 a[N], d[N];
std::vector<int> g[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 2; i <= n; i++) std::cin >> p[i], dep[i] = dep[p[i]] + 1, g[dep[i]].push_back(i);
  int mx = *std::max_element(dep + 1, dep + n + 1);
  for (int i = mx; i >= 0; i--) {
    i64 cur = 0;
    for (auto j : g[i]) cur += a[j];
    if (cur != 0) {
      std::cout << (cur > 0 ? "+\n" : "-\n");
      return;
    }
  }
  if (a[1] > 0) std::cout << "+\n";
  else if (a[1] == 0) std::cout << "0\n";
  else std::cout << "-\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
