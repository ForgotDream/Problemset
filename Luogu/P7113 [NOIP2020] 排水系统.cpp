/**
 * @file    P7113 [NOIP2020] 排水系统.cpp
 * @author  ForgotDream
 * @brief   Topo Sort
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
using i128 = __int128;
constexpr int N = 1e5 + 50;
int n, m, deg[N];
std::vector<int> adj[N];
struct Frac {
  i128 up = 0, dwn = 0;
  Frac(i128 _u = 0, i128 _d = 1) { up = _u, dwn = _d, simp(); }
  void simp() {
    i128 g = std::__gcd(up, dwn);
    up /= g, dwn /= g;
  }
  Frac operator+(Frac &rhs) {
    simp(), rhs.simp();
    return Frac(up * rhs.dwn + dwn * rhs.up, dwn * rhs.dwn);
  }
  Frac operator/(int d) {
    assert(d), simp();
    return Frac(up, dwn * d);
  }
  Frac operator+=(Frac rhs) { return *this = *this + rhs; }
  Frac operator/=(int val) { return *this = *this / val; }
} f[N];
int cnt, out[N];
void print(i128 num) {
  if (num / 10) print(num / 10);
  std::cout.put(char(num % 10 + '0'));
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1, k, j; i <= n; i++) {
    std::cin >> k;
    if (!k) out[++cnt] = i;
    while (k--) std::cin >> j, adj[i].push_back(j), deg[j]++;
  }
  std::queue<int> q;
  for (int i = 1; i <= m; i++) q.push(i), f[i] = Frac(1, 1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    Frac d(0, 1);
    if (!adj[u].empty()) d = f[u] / adj[u].size();
    for (auto v : adj[u]) {
      f[v] += d;
      if (!--deg[v]) q.push(v);
    }
  }
  for (int i = 1; i <= cnt; i++) {
    print(f[out[i]].up), std::cout << " ";
    print(f[out[i]].dwn), std::cout << "\n";
  }
  return 0;
}