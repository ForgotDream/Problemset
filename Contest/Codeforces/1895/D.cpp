#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N], dig[N][40], cnt[N], ans[N], b[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i < n; i++) std::cin >> a[i];
  for (int i = 1; i < n; i++) {
    for (int j = std::__lg(n - 1); ~j; j--) {
      if (a[i] & (1 << j)) dig[i + 1][j] = dig[i][j] ^ 1;
      else dig[i + 1][j] = dig[i][j];
      cnt[j] += dig[i + 1][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = std::__lg(n - 1); ~j; j--) if (i & (1 << j)) ans[j]++;
  }
  for (int i = 0; i <= std::__lg(n - 1); i++) {
    if (cnt[i] != ans[i]) b[1] += (1 << i);
  }
  for (int i = 1; i < n; i++) {
    b[i + 1] = b[i];
    for (int j = std::__lg(n - 1); ~j; j--) {
      if (a[i] & (1 << j)) b[i + 1] ^= (1 << j);
    }
  }
  for (int i = 1; i <= n; i++) std::cout << b[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}