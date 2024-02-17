#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 505;

int h, w, n;
char s[N][N];
std::string t;

std::map<char, pii> mp = {
    {'L', {0, -1}},
    {'R', {0, 1}},
    {'U', {-1, 0}},
    {'D', {1, 0}},
};

void solve() {
  std::cin >> h >> w >> n >> t;
  for (int i = 1; i <= h; i++) std::cin >> (s[i] + 1);

  int ans = 0;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      if (s[i][j] == '#') continue;
      int x = i, y = j;
      bool flg = true;
      for (auto c : t) {
        x += mp[c].first, y += mp[c].second;
        if (s[x][y] == '#') {
          flg = false;
          break;
        }
      }
      ans += flg;
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
