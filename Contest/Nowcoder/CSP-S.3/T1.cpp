#include <algorithm>
#include <deque>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, a[N], b[N];
std::deque<i64> A, B;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i];
  std::sort(a + 1, a + 1 + n, std::greater<>());
  std::sort(b + 1, b + 1 + m, std::greater<>());
  for (int i = 1; i <= n; i++) A.push_back(a[i]);
  for (int i = 1; i <= m; i++) B.push_back(b[i]);
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    i64 x = A.front() * B.front(), y = A.back() * B.back();
    if (x >= y) {
      ans += x;
      A.pop_front(), B.pop_front();
    } else {
      ans += y;
      A.pop_back(), B.pop_back();
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
