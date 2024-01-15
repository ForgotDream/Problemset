#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

i64 n;

i64 fastPow(i64 base, i64 exp) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) res *= base;
    base *= base;
  }
  return res;
}

void solve() {
  std::cin >> n;
  i64 ans = 0;
  for (int i = 18; ~i; i--) {
    i128 pw = fastPow(5, i);
    for (int j = 4; ~j; j--) {
      if (n > j * pw) {
        n -= j * pw, ans += 2 * j * fastPow(10, i);
        break;
      }
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
