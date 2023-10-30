#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, typ, a[N];
int f[N], g[N];
void solve() {
  std::cin >> n >> typ;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    int min = a[i], max = a[i];
    for (int j = i; j; j--) {
      min = std::min(min, a[j]), max = std::max(max, a[j]);
      if (min == std::min(a[i], a[j])) continue;
      if (max == std::max(a[i], a[j])) continue;
      f[i]++;
    }
    min = a[i], max = a[i];
    for (int j = i; j <= n; j++) {
      min = std::min(min, a[j]), max = std::max(max, a[j]);
      if (min == std::min(a[i], a[j])) continue;
      if (max == std::max(a[i], a[j])) continue;
      g[i]++;
    }
  }
  for (int i = 1; i <= n; i++) std::cout << g[i] << " \n"[i == n];
  for (int i = 1; i <= n; i++) std::cout << f[i] << " \n"[i == n];
}

int main() {
  freopen("interval.in", "r", stdin);
  freopen("interval.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
