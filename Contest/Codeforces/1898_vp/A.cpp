#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 105;
int n, k;
char s[N];

void solve() {
  std::cin >> n >> k >> (s + 1);
  int sum = std::count(s + 1, s + n + 1, 'B');
  for (int i = 0, p = sum; i <= n; i++) {
    if (s[i] == 'B') p--;
    if (i + p == k) {
      if (i == 0) std::cout << 0 << "\n";
      else std::cout << 1 << "\n" << i << " B\n";
      return;
    }
  }
  for (int i = 0, p = n - sum; i <= n; i++) {
    if (s[i] == 'A') p--;
    if (i + p == n - k) {
      if (i == 0) std::cout << 0 << "\n";
      else std::cout << 1 << "\n" << i << " A\n";
      return;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
