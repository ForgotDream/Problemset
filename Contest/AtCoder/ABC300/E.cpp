#include <atcoder/modint.hpp>
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  i64 n;
  std::cin >> n;

  i64 copy = n;
  std::vector<int> factor(6);
  for (auto i : {5, 3, 2}) {
    while (copy % i == 0) {
      copy /= i;
      factor[i]++;
    }
    if (copy == 1) {
      break;
    }
  }

  if (copy != 1) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::map<i64, atcoder::modint998244353> mp;

  std::function<atcoder::modint998244353(i64)> dfs = [&](i64 cur) -> atcoder::modint998244353 {
    if (cur == n) {
      return 1;
    } else if (cur > n) {
      return 0;
    } else if (mp.count(cur)) {
      return mp[cur];
    }

    atcoder::modint998244353 res = 0;
    for (int i = 2; i <= 6; i++) {
      res += dfs(i * cur) / 6;
    }

    return mp[cur] = res * atcoder::modint998244353(6) / atcoder::modint998244353(5);
  };

  std::cout << dfs(1).val() << "\n";

  return 0;
}