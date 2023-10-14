#include <algorithm>
#include <cstring>
#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

constexpr int N = 1e5 + 50, M = 100;
int o, m, q, n;
i64 a[N], b[N], na[M], nb[M];
namespace N_LESS_THAN_1E5 {
i128 f[N];
void solve() {
  memset(f, 0x3f, sizeof(f));
  f[0] = 0;
  for (int i = 1; i <= n; i++) {
    for (u64 j = na[i]; j <= 1e5; j++) {
      f[j] = std::min(f[j], f[j - na[i]] + nb[i]);
    }
  }
  for (int i = 1; i <= 1e5; i++) f[i] += f[i - 1];
  for (i64 u; q; q--) std::cin >> u, std::cout << static_cast<u64>(f[u - 1]) << "\n";
}
}  // namespace N_LESS_THAN_1E5
namespace SHABI {
using f80 = long double;
struct Node {
  u64 a, b;
  bool operator<(const Node &rhs) const {
    f80 l = static_cast<f80>(b) / a, r = static_cast<f80>(rhs.b) / rhs.a;
    if (l != r) return l < r;
    return a > b;
  }
} b[M];
void solve() {
  for (int i = 1; i <= n; i++) b[i].a = na[i], b[i].b = nb[i];
  std::sort(b + 1, b + n + 1);
  for (i64 u; q; q--) {
    std::cin >> u;
    u64 ans = 0;
    for (int i = 1; i <= n; i++) {
      i64 d = u / b[i].a;
      ans += d * b[i].b, u -= d * b[i].a;
    }
    std::cout << ans << "\n";
  }
}
}  // namespace SHABI
namespace O_EQUALS_TO_1 {
void solve() {
  for (i64 u; q; q--) {
    std::cin >> u;
    u64 a = u, b = u + 1;
    if (u & 1) b /= 2;
    else a /= 2;
    std::cout << a * b * nb[1] << "\n";
  }
}
}  // namespace O_EQUALS_TO_1
void solve() {
  std::cin >> m >> q;
  for (int i = 1; i <= m; i++) std::cin >> a[i] >> b[i];
  n = 0;
  na[++n] = a[1], nb[n] = b[1];
  for (int i = 2; i <= m; i++) {
    if (a[i] != a[i - 1]) na[++n] = a[i], nb[n] = b[i];
    else nb[n] = std::min(nb[n], b[i]);
  }
  if (o == 1) O_EQUALS_TO_1::solve();
  N_LESS_THAN_1E5::solve();
  // SHABI::solve();
}

int main() {
  freopen("paradise.in", "r", stdin);
  freopen("paradise.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t >> o;
  while (t--) solve();
  return 0;
}
