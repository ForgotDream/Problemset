/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  std::vector<int> cnta(n + 1), cntb(n + 1);

  for (int i = 0; i < n; i++) std::cin >> a[i], cnta[a[i]]++;
  for (int i = 0; i < n; i++) std::cin >> b[i], cntb[b[i]]++;

  for (int i = n - 2; ~i; i--) {
    bool flg = true;

    

    if (flg) {
      std::cout << i + 1 << "\n";
      return;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
