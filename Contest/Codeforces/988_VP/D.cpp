#include <iostream>
#include <set>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N];
std::set<i64> s;
int ans, p[2];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], s.insert(a[i]);
  ans = 1, p[0] = a[1];
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 31; j++) {
      i64 d = 1ll << j;
      if (s.find(a[i] - d) != s.end() && s.find(a[i] + d) != s.end()) {
        std::cout << 3 << "\n";
        std::cout << a[i] - d << " " << a[i] << " " << a[i] + d << "\n";
        return;
      }
      if (s.find(a[i] - d) != s.end()) ans = 2, p[0] = a[i] - d, p[1] = a[i];
      if (s.find(a[i] + d) != s.end()) ans = 2, p[0] = a[i], p[1] = a[i] + d;
    }
  }
  std::cout << ans << "\n";
  for (int i = 0; i < ans; i++) std::cout << p[i] << " \n"[i == ans - 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
