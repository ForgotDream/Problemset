/**
 * @file    CF1768F Wonderful Jump.cpp
 * @author  ForgotDream
 * @brief   Nice DP!
 * @date    2023-12-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 50;
int n, a[N];
i64 f[N];
int s[N], top;
i64 nijou(int u) { return 1ll * u * u; }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  memset(f, 0x3f, sizeof(f)), f[1] = 0, s[++top] = 1;
  int b = std::sqrt(n);
  for (int i = 2; i <= n; i++) {
    int mn = a[i];
    for (int j = i - 1; j && j >= i - b; j--) {
      mn = std::min(mn, a[j]);
      f[i] = std::min(f[i], f[j] + mn * nijou(i - j));
    }
    while (top && a[i] < a[s[top]]) top--;
    for (int j = 1; j <= b && j <= top; j++) {
      f[i] = std::min(f[i], f[s[j]] + a[s[j]] * nijou(i - s[j]));
    }
    s[++top] = i;
    if (a[i] < b) {
      for (int j = i - 1; j; j--) {
        if (a[i] >= a[j]) break;
        f[i] = std::min(f[i], f[j] + a[i] * nijou(i - j));
      }
    }
  }
  for (int i = 1; i <= n; i++) std::cout << f[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
