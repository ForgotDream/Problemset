#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int n, m, a[N];
i64 ans;
i64 calc(int i) {
  if (a[i] == a[i - 1]) return n - i + 1;
  return 1ll * (i - 1) * (n - i + 1) + n - i + 1;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i], ans += calc(i);
  while (m--) {
    int i, x;
    std::cin >> i >> x;
    ans -= calc(i) + calc(i + 1);
    a[i] = x;
    ans += calc(i) + calc(i + 1);
    std::cout << ans << "\n";
  }
  return 0;
}