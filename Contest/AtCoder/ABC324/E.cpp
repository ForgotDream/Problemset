#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 5e5 + 50;
int n;
std::string s[N], t;
i64 pre[N], suf[N], sum[N];
void solve() {
  std::cin >> n >> t;
  for (int i = 1; i <= n; i++) {
    std::cin >> s[i];
    int p = 0, cur = 0;
    for (int j = 0; j < t.length(); j++) {
      while (p < s[i].length() && s[i][p] != t[j]) p++;
      if (p != s[i].length()) cur = j + 1, p++;
      else break;
    }
    pre[cur]++;
    p = s[i].length() - 1, cur = 0;
    for (int j = t.length() - 1; ~j; j--) {
      while (p >= 0 && s[i][p] != t[j]) p--;
      if (p != -1) cur = t.length() - j, p--;
      else break;
    }
    suf[cur]++;
  }
  for (int i = t.length(); i >= 0; i--) sum[i] = sum[i + 1] + pre[i];
  i64 ans = 0;
  for (int i = 0; i <= t.length(); i++) {
    ans += suf[i] * sum[t.length() - i];
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
