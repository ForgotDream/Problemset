#include <bits/stdc++.h>
#define int long long

using i64 = long long;

int fastPow(int base, int exp) {
  int res = 1;
  while (exp) {
    if (exp & 1) {
      res *= base;
    }
    base *= base;
    exp >>= 1;
  }
  return res;
}

signed main() {
  // freopen("test.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto calc = [&](int m, int n) {
    int p = fastPow(m, n);
    
    auto valid = [&](int num) {
      for (int i = 1; i <= n; i++) {
        if (num % m == 0) {
          num /= m;
        } else {
          num += 1;
        }
      }
      return num == 1;
    };
    
    int ans = 0;
    for (int i = 1; i <= p; i++) {
      if (valid(i)) {
        std::cout << i << "\n";
        ans++;
      }
    }

    return ans;
  };

  std::cout << calc(2, 3) << "\n";

  return 0;
}