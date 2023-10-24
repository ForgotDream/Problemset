#include <cmath>
#include <iostream>
#include <string>

using i64 = long long;

int n, cnt[10], tmp[10];
i64 ans;
std::string s;
void solve() {
  std::cin >> n >> s;
  for (int i = 0; i < s.length(); i++) cnt[s[i] - '0']++;
  int ans = 0;
  for (int i = 0; i <= 1e7; i++) {
    for (int i = 0; i < 10; i++) tmp[i] = 0;
    i64 sqr = 1ll * i * i;
    while (sqr) tmp[sqr % 10]++, sqr /= 10;
    if (cnt[0] < tmp[0]) continue;
    bool flg = true;
    for (int i = 1; i < 10; i++) {
      if (tmp[i] != cnt[i]) {
        flg = false;
        break;
      }
    }
    if (flg) ans++;
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
