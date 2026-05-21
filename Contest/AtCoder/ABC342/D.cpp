#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

constexpr int N = 2e5 + 50;

int n, a[N];

int prime[N], cnt;
bool is_not_prime[N];

std::random_device rd;
std::mt19937_64 rng(rd());

u64 p[N], val[N], mod = rng();

void solve() {
  for (int i = 0; i < N; i++) p[i] = rng() % mod;

  i64 ans = 0, t = 0;
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    if (a[i] == 0) t++;
  }
  ans += t * (t - 1) / 2 + t * (n - t);

  for (int i = 1; i <= n; i++) {
    int cpy = a[i];
    for (int j = 2; j * j <= cpy; j++) {
      if (cpy % j == 0) {
        int cur = 0;
        while (cpy % j == 0) cpy /= j, cur++;
        cur %= 2, (val[i] += cur * p[j]) %= mod;
      }
    }
    if (cpy != 1) (val[i] += p[cpy]) %= mod;
  }

  std::map<u64, int> mp;
  for (int i = 1; i <= n; i++) if (a[i]) mp[val[i]]++;

  for (auto [v, c] : mp) {
    ans += 1ll * c * (c - 1) / 2;
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
