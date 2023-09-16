#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using i64 = long long;
using f80 = long double;

int n;
std::string s, t, ans = "", limit = "";
std::vector<int> d;
void dfs(int u, std::string a, std::string b) {
  if (u == n + 1) {
    if (ans < a + b) ans = a + b;
    return;
  }
  dfs(u + 1, a + s[u], b + t[u]);
  dfs(u + 1, a, b);
}
void dfs2(int u, std::string a, std::string b) {
  if (u == d.size()) {
    if (ans < a + b) {
      ans = a + b;
    }
    if (f80(std::clock()) / CLOCKS_PER_SEC >= 0.92) {
      std::cout << ans;
      exit(0);
    }
    return;
  }
  dfs2(u + 1, a + s[d[u]], b + t[d[u]]);
  dfs2(u + 1, a, b);
}
void solve() {
  std::cin >> s >> t;
  n = s.size();
  int maxl = 0, pos;
  for (int i = 0; i < n; i++) {
    if (s[i] > maxl) {
      maxl = s[i];
      pos = i;
    }
  }
  if (n <= 20) {
    dfs(pos, "", "");
    std::cout << ans << "\n";
    return;
  }
  if (s == t) {
    int num = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == maxl) num++;
    }
    for (int i = 1; i <= num; i++) ans += (char)maxl;
    std::cout << ans + ans << "\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    if (s[i] == maxl) {
      d.push_back(i);
      pos = i;
    }
  }
  for (int i = pos + 1; i < n; i++) d.push_back(i);
  dfs2(0, "", "");
  std::cout << ans << "\n";
}

signed main() {
  std::freopen("xiao.in", "r", stdin);
  std::freopen("xiao.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
