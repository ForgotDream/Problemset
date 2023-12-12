/**
 * @file    CF1904D Set To Max.cpp
 * @author  ForgotDream
 * @brief   Monotonic Stack
 * @date    2023-12-10
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, a[N], b[N];
bool f[N];
int piv[N], pre[N], nxt[N];
void solve() {
  std::cin >> n;
  memset(f, false, sizeof(bool) * (n + 1));
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  for (int t = 2; t; t--) {
    std::stack<int, std::vector<int>> s;
    s.push(n + 1), a[n + 1] = 2e9;
    for (int i = n; i >= 1; i--) {
      while (a[s.top()] <= a[i]) s.pop();
      nxt[i] = s.top(), s.push(i);
    }
    while (!s.empty()) s.pop();
    s.push(0), b[0] = 0;
    for (int i = 1; i <= n; i++) {
      while (b[s.top()] >= b[i]) s.pop();
      pre[i] = s.top(), s.push(i);
    }
    memset(piv, 0, sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
      piv[a[i]] = i;
      if (piv[b[i]] && a[i] <= b[i]) {
        f[i] |= (pre[i] < piv[b[i]]) && (nxt[piv[b[i]]] > i);
      }
    }
    std::reverse(a + 1, a + n + 1), std::reverse(b + 1, b + n + 1);
    std::reverse(f + 1, f + n + 1);
  }
  bool ans = true;
  for (int i = 1; i <= n; i++) ans &= f[i];
  std::cout << (ans ? "YES" : "NO") << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
