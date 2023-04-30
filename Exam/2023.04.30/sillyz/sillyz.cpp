#include <bits/stdc++.h>

using i64 = long long;

namespace Helper {
void useFileIO() {
  freopen("sillyz.in", "r", stdin);
  freopen("sillyz.out", "w", stdout);
  return;
}
};

int main() {
  Helper::useFileIO();

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  i64 a, b;
  std::cin >> a >> b;

  i64 ans = 0;
  for (int i = 1; i <= b; i++) {
    int copy = i;
    std::vector<int> nums;

    while (copy) {
      nums.push_back(copy % 10);
      copy /= 10;
    }

    i64 tmp = 1;
    for (int j = 0; j < nums.size(); j++) {
      tmp *= nums[j];
    }
    tmp *= i;

    if (tmp >= a && tmp <= b) {
      ans++;
    }
  }

  std::cout << ans << "\n";

  return 0;
}