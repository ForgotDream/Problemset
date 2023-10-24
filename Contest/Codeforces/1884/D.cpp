#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, a[N], b[N];
i64 sum[N], tot[N];
int prime[N], mu[N], cnt;
bool isNotPrime[N];
void getMu(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true, mu[i * prime[j]] = -mu[i];
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) sum[i] = tot[i] = b[i] = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b[a[i]]++;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) sum[j] += b[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) tot[j] += mu[i] * (sum[j / i] != 0);
  }
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    i64 cur = 0;
    for (int j = i; j <= n; j += i) cur += b[j];
    ans += cur * cur * tot[i];
  }
  std::cout << (1ll * n * n - ans) / 2 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  getMu(1e6);
  while (t--) solve();
  return 0;
}
