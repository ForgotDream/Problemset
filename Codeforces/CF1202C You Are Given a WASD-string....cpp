/**
 * @file    CF1202C You Are Given a WASD-string....cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-31
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 2e5 + 50;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
std::string s;
int up[N], dn[N], lt[N], rt[N];
int revup[N], revdn[N], revlt[N], revrt[N];
void solve() {
  std::cin >> s;
  int n = s.length();
  s = '\0' + s;
  int curx = 0, cury = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'W') curx--;
    else if (s[i] == 'A') cury--;
    else if (s[i] == 'S') curx++;
    else cury++;
    up[i] = std::min(up[i - 1], curx);
    dn[i] = std::max(dn[i - 1], curx);
    lt[i] = std::min(lt[i - 1], cury);
    rt[i] = std::max(rt[i - 1], cury);
  }
  revup[n + 1] = revdn[n + 1] = curx;
  revlt[n + 1] = revrt[n + 1] = cury;
  for (int i = n; i >= 1; i--) {
    if (s[i] == 'W') curx++;
    else if (s[i] == 'A') cury++;
    else if (s[i] == 'S') curx--;
    else cury--;
    revup[i] = std::min(revup[i + 1], curx);
    revdn[i] = std::max(revdn[i + 1], curx);
    revlt[i] = std::min(revlt[i + 1], cury);
    revrt[i] = std::max(revrt[i + 1], cury);
  }
  i64 ans = 1ll * (dn[n] - up[n] + 1) * (rt[n] - lt[n] + 1);
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k < 4; k++) {
      int cup = std::min(up[i], revup[i + 1] + d[k][0]);
      int cdn = std::max(dn[i], revdn[i + 1] + d[k][0]);
      int clt = std::min(lt[i], revlt[i + 1] + d[k][1]);
      int crt = std::max(rt[i], revrt[i + 1] + d[k][1]);
      ans = std::min(ans, 1ll * (cdn - cup + 1) * (crt - clt + 1));
    }
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}