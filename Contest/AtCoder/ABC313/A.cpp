#include <bits/stdc++.h>
using i64 = long long;
int n, a[105], max;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  max = *std::max_element(a + 2, a + n + 1);
  if (a[1] > max) std::cout << 0 << "\n";
  else std::cout << 1 + max - a[1] << "\n";
  return 0;
}