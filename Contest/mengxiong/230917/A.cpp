#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>
#include <vector>

using i64 = long long;

constexpr int N = 1050;
int prime[N], cnt;
bool np[N];
void getPrime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!np[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && prime[j] * i <= n; j++) {
      np[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}
int a[N], p;
inline std::string print() {
  std::string res =  "{";
  for (int i = 1; i <= p; i++) {
    std::string tmp;
    int cpy = a[i];
    while (cpy) tmp += (cpy % 10 + '0'), cpy /= 10;
    std::reverse(tmp.begin(), tmp.end());
    res += tmp;
    if (i != p) res += ",";
  }
  res += "},";
  return res;
}
int lim;
std::string ans = "vector<vector<int>>ans={";
void dfs(int idx, int sum) {
  if (idx > cnt || sum > lim) return;
  if (sum == lim) return void(ans += print());
  dfs(idx + 1, sum);
  a[++p] = prime[idx];
  dfs(idx, sum += prime[idx]);
  --p;
}
i64 l, r;
void solve() {
  std::cin >> l >> r;
  getPrime(95);
  for (int i = 1; i <= 95; i++) lim = i, dfs(1, 0);
  std::cerr << ans.length() << "\n";
  std::cout << ans.substr(l - 1, r - l + 1) << "\n";
}

int main() {
  std::freopen("list.in", "r", stdin);
  std::freopen("list.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
