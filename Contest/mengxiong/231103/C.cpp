#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50, mod = 998244353;
// --- Comb Utils ---
i64 fac[N], ifc[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init(int n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[n] = fastPow(fac[n], mod - 2, mod);
  for (int i = n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}
inline i64 C(i64 n, i64 m) {
  if (m > n) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod;
}
// ------------------
int n, k, nxt[N];
char s[N];
std::vector<int> adj[N];
int dep[N], siz[N];
i64 ans;
void dfs(int u) {
  dep[u] = dep[nxt[u]] + 1, siz[u] = 1;
  for (auto v : adj[u]) dfs(v), siz[u] += siz[v];
  i64 cnt = C(siz[u], k) % mod;
  for (auto v : adj[u]) cnt = (cnt - C(siz[v], k) + mod) % mod;
  ans = (ans + cnt * dep[u] % mod * dep[u] % mod) % mod;
}
void solve() {
  std::cin >> k >> (s + 1);
  n = strlen(s + 1);
  init(n + 10);
  for (int i = 2; i <= n; i++) {
    int j = nxt[i - 1];
    while (j && s[j + 1] != s[i]) j = nxt[j];
    if (s[j + 1] == s[i]) j++;
    nxt[i] = j;
  }
  for (int i = 1; i <= n; i++) adj[nxt[i]].push_back(i);
  dfs(0);
  std::cout << ans << "\n";
}

int main() {
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
