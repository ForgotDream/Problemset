#include <string>
#include <iostream>

using i64 = long long;

constexpr int N = 105;
std::string s, t;
int n, m, cnt;
int d[2 * N];
int manacher(std::string t) {
  int len = t.length();
  std::string tmp(2 * N, '\0');
  tmp[0] = '$', cnt = 0, t = '\0' + t;
  for (int i = 1; i <= len; i++) tmp[++cnt] = '#', tmp[++cnt] = t[i];
  tmp[++cnt] = '#', tmp[++cnt] = '|';
  int r = 0, mid = 0, res = 0;
  for (int i = 1; i <= cnt; i++) {
    d[i] = (i < r) ? std::min(d[(mid << 1) - i], d[mid] + mid - i) : 1;
    while (tmp[i + d[i]] == tmp[i - d[i]]) d[i]++;
    res = std::max(res, d[i]);
    if (d[i] + i > r) r = d[i] + i, mid = i;
  }
  return res - 1;
}
int ans;
void dfs(int i, int j, std::string cur) {
  if (i == n && j == m) {
    ans = std::max(ans, manacher(cur));
    return;
  }
  if (i < n) dfs(i + 1, j, cur + s[i + 1]);
  if (j < m) dfs(i, j + 1, cur + t[j + 1]);
}
void solve() {
  std::cin >> s >> t;
  n = s.length(), m = t.length();
  s = '\0' + s, t = '\0' + t;
  dfs(0, 0, "");
  std::cout << ans << "\n";
}

int main() {
  std::freopen("a.in", "r", stdin);
  std::freopen("a.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}