#include <string>
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 505, mod = 1e9 + 7;
int n;
std::string s[N];
int l[N], f[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> l[i] >> s[i], s[i] = '\0' + s[i];
  i64 d = l[1];
  for (int i = 2; i <= n; i++) d = std::lcm(d, l[i]);
  for (int i = 1; i <= d; i++) {
    int cur = 0;
    for (int j = 1; j <= n; j++) {
      if (s[j][(i - 1) % l[j] + 1] == 'o') cur++;
    }
    f[cur]++;
  }
  i64 coef = 1;
  for (int i = 50; i >= 2; i--) {
    if (d % i == 0) d /= i;
    else (coef *= i) %= mod;
  }
  for (int i = 1; i <= n; i++) std::cout << coef * f[i] % mod << "\n";
}

int main() {
  // std::freopen("meeting.in", "r", stdin);
  // std::freopen("meeting.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}