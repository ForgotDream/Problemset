#include <bits/stdc++.h>
int t;
std::string s;
void solve() {
  std::cin >> s;
  std::string t = "Yes";
  auto idx = std::find(t.begin(), t.end(), s[0]);
  if (idx == t.end()) return void(std::cout << "NO\n");
  int p = idx - t.begin();
  for (int i = 0; i < s.length(); i++, (p += 1) %= 3) {
    if (s[i] != t[p]) return void(std::cout << "NO\n");
  }
  std::cout << "YES\n";
  return;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}