#include <iostream>
#include <string>
#include <unordered_map>

using i64 = long long;

constexpr int N = 5e4 + 50;
int n, m;
std::string s[N];
int conv(char c) { return c == '?' ? 0 : c - 'a' + 1; }
namespace M_LESS_THAN_2 {
constexpr int K = 27;
int cnt[K][K];
void solve() {
  i64 ans = 0;
  m = 2;
  for (int i = 1; i <= n; i++) {
    while (s[i].length() < m) s[i] += '?';
    int p[2] = {0};
    auto calc = [&](auto &self, int idx) -> int {
      if (idx == m) return cnt[p[0]][p[1]];
      int res = 0;
      if (s[i][idx] == '?') {
        for (int i = 0; i <= 26; i++) {
          p[idx] = i;
          res += self(self, idx + 1);
        }
      } else {
        p[idx] = 0;
        res += self(self, idx + 1);
        p[idx] = s[i][idx] - 'a' + 1;
        res += self(self, idx + 1);
      }
      return res;
    };
    ans += calc(calc, 0);
    cnt[conv(s[i][0])][conv(s[i][1])]++;
  }
  std::cout << ans << "\n";
}
}  // namespace M_LESS_THAN_2
namespace FULL_COMBO {
void solve() {
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      bool flg = true;
      for (int k = 0; k < m; k++) {
        if (s[i][k] != '?' && s[j][k] != '?' && s[i][k] != s[j][k]) {
          flg = false;
          break;
        }
      }
      ans += flg;
    }
  }
  std::cout << ans << "\n";
}
}  // namaespace FULL_COMBO
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> s[i];
  if (m <= 2) M_LESS_THAN_2::solve();
  else FULL_COMBO::solve();
}

int main() {
  std::freopen("parametriziran.in", "r", stdin);
  std::freopen("parametriziran.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
