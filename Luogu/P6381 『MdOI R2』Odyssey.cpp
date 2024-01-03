/*
 * @file    P6381 『MdOI R2』Odyssey.cpp
 * @author  ForgotDream
 * @brief   DP + Hash
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 1e5 + 50, M = 2e5 + 50;
constexpr u64 base = 2333;
int n, m, k;
struct Edge {
  int u, v, l, w;
} edges[M];
std::vector<int> adj[N / 100];
int deg[N];

int prime[N], cnt;
bool isNotPrime[N];
void getPrime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}

u64 pw[N];
void init() {
  getPrime(1e5);
  pw[0] = 1;
  for (int i = 1; i <= cnt; i++) pw[i] = base * pw[i - 1];
}

u64 hsh[N], rev[N];
void calcHash(int w) {
  if (hsh[w] || rev[w]) return;
  int p = w;
  for (int i = 1; i <= cnt && prime[i] * prime[i] <= p; i++) {
    if (p % prime[i] == 0) {
      int coef = 0;
      while (p % prime[i] == 0) p /= prime[i], coef++;
      coef %= k;
      hsh[w] += pw[i] * coef;
      coef = (k - coef) % k;
      rev[w] += pw[i] * coef;
    }
  }
  if (p != 1) {
    int d = std::lower_bound(prime + 1, prime + cnt + 1, p) - prime, coef = 1;
    coef %= k;
    hsh[w] += pw[d] * coef;
    coef = (k - coef) % k;
    rev[w] += pw[d] * coef;
  }
}

std::map<u64, int> f[N];

void solve() {
  init();

  std::cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    auto &[u, v, l, w] = edges[i];
    std::cin >> u >> v >> w >> l, adj[u].push_back(i), deg[v]++;
    calcHash(w);
  }

  std::queue<int> q;
  for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);

  int ans = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto i : adj[u]) {
      auto [_, v, l, w] = edges[i];
      f[v][hsh[w]] = std::max(f[v][hsh[w]], l);
      if (f[u].contains(rev[w])) {
        f[v][hsh[w]] = std::max(f[v][hsh[w]], f[u][rev[w]] + l);
      }
      ans = std::max(ans, f[v][hsh[w]]);
      if (!--deg[v]) q.push(v);
    }
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
