#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 c[] = {1,         11,         111,         1111,
                     11111,     111111,     1111111,     11111111,
                     111111111, 1111111111, 11111111111, 111111111111};
int n;
void solve() {
  std::cin >> n;
  std::vector<i64> vec;
  auto calc = [&](auto &self, int dep, int idx, i64 cur) {
    if (dep == 3)
      return vec.push_back(cur);
    for (int i = idx; i < 12; i++) self(self, dep + 1, i, cur + c[i]);
  };
  calc(calc, 0, 0, 0);
  std::sort(vec.begin(), vec.end());
  std::cout << vec[n - 1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--)
    solve();
  return 0;
}
