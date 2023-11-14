#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50;
int n, d, L, R, q, x[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> d >> L >> R >> q;
  for (int i = 1; i <= q; i++) std::cin >> x[i];
  for (int i = 1; i <= q; i++) {
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
