#include <bits/stdc++.h>

using i64 = long long;

namespace Helper {
void useFileIO() {
  freopen("set.in", "r", stdin);
  freopen("set.out", "w", stdout);
  return;
}
};

constexpr i64 MOD = 1000000001;

int main() {
  Helper::useFileIO();

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  i64 ans = 0;
  for (int i = 0; i < (1 << n); i++) {
    std::vector<int> cur;

    for (int j = 0; (1 << j) <= i; j++) {
      if (i & (1 << j)) {
        cur.push_back(j + 1);
      }
    }

    bool flg = true;
    for (int j = 0; j < cur.size(); j++) {
      for (int k = j + 1; k < cur.size(); k++) {
        if (2 * cur[j] == cur[k] || 3 * cur[j] == cur[k]) {
          flg = false;
          break;
        }
      }  
    }

    if (flg) {
      (ans += 1) %= MOD;
    }
   }

  std::cout << ans << "\n";

  return 0;
}