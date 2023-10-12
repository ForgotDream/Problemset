#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 3;
int n;
char s[N];
// --- Comb Utils ---
i64 c[][3] = {{1}, {1, 1}, {1, 2, 1}};
i64 lucas(i64 n, i64 m) {
  if (!m) return 1;
  return c[n % mod][m % mod] * lucas(n / mod, m / mod);
}
// ------------------
void solve() {
  std::cin >> n >> s;
  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    (ans += lucas(n - 1, i) * (s[i] - 'A') % mod) %= mod;
  }
  if (!(n & 1)) ans = (mod - ans % mod) % mod;
  std::cout << char((ans + mod) % mod + 'A') << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
