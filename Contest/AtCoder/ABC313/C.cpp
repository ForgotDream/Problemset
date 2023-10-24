#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int n, a[N];
i64 sum, rst, ans;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], sum += a[i];
  rst = sum % n, sum /= n;
  for (int i = 1; i <= n; i++) {
    if (rst && a[i] > sum + 1) ans += a[i] - sum - 1, rst--;
    else if (a[i] > sum) ans += std::abs(a[i] - sum);
  }
  std::cout << ans << "\n";
  return 0;
}