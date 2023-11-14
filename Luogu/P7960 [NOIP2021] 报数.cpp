/**
 * @file    P7960 [NOIP2021] 报数.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-11-13
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e7 + 50;
int n, nxt[N];
bool invalid[N];
inline bool check(int u) {
  while (u) {
    if (u % 10 == 7) return false;
    u /= 10;
  }
  return true;
}
void init() {
  for (int i = 1; i <= 1e7; i++) {
    if (invalid[i]) continue;
    if (!check(i)) {
      for (int j = i; j <= 1e7; j += i) invalid[j] = true;
    }
  }
  for (int i = 1e7; i; i--) {
    if (invalid[i + 1]) nxt[i] = nxt[i + 1];
    else nxt[i] = i + 1;
  }
}
void solve() {
  std::cin >> n;
  init();
  for (int x; n; n--) {
    std::cin >> x;
    if (invalid[x]) std::cout << -1 << "\n";
    else std::cout << nxt[x] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
