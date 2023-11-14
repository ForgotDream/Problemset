#include <algorithm>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using f80 = long double;

constexpr int N = 70;
i64 n, k, cnt[N], tmp[N];
f80 fac[N];
void solve() {
  std::cin >> n >> k;
  int m = std::__lg(n);
  for (int i = 0; i <= m; i++) cnt[i] = n / (1ll << i);
  for (int i = m; ~i; i--) {
    for (int j = i + 1; j <= m; j++) cnt[i] -= cnt[j];
    tmp[i] = cnt[i];
  }
  fac[0] = 1;
  for (int i = 1; i <= 20; i++) fac[i] = i * fac[i - 1];
  int p = m, q = 0, tot = 0;
  for (; ~p; p--) {
    bool flg = false;
    for (q = 1; q <= cnt[p]; q++) {
      if (fac[tot + q] > k) {
        flg = true;
        break;
      }
    }
    tot += (--q);
    if (flg) break;
  }
  std::cout << p << " " << q << " " << tot << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
