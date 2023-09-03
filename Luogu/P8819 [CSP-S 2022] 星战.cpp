/**
 * @file    P8819 [CSP-S 2022] 星战.cpp
 * @author  ForgotDream
 * @brief   Hash
 * @date    2023-09-02
 */
#include <iostream>
#include <random>

using i64 = long long;
using u64 = unsigned long long;

std::random_device rd;
std::mt19937 rng(rd());
constexpr int N = 5e5 + 50;
int n, m, q;
u64 sum, a[N], init[N], cur, hash[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) a[i] = rng(), sum += a[i];
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    init[v] += a[u], cur += a[u];
  }
  for (int i = 1; i <= n; i++) hash[i] = init[i];
  std::cin >> q;
  while (q--) {
    int opt, u, v;
    std::cin >> opt;
    if (opt == 1) std::cin >> u >> v, hash[v] -= a[u], cur -= a[u];
    else if (opt == 2) std::cin >> u, cur -= hash[u], hash[u] = 0;
    else if (opt == 3) std::cin >> u >> v, hash[v] += a[u], cur += a[u];
    else std::cin >> u, cur += init[u] - hash[u], hash[u] = init[u];
    if (cur == sum) std::cout << "YES\n";
    else std::cout << "NO\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}