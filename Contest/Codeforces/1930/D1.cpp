#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 105;

int n;
char s[N];

void solve() {
  std::cin >> n >> (s + 1);

  i64 ans = 0;
  for (int l = 1; l <= n; l++) {
    for (int r = l; r <= n; r++) {
      for (int i = l; i <= r; i++) {
        if (s[i] == '1') ans++, i += 2;
      }
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
