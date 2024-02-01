/*
 * @file    P5330 [SNOI2019] 数论.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e6 + 50;

int P, Q, n, m, A[N], B[N];
i64 T;

bool vis[N], buc[N];
int nxt[N], bln[N], cnt, val[N], s[N], len, pos[N];

int sum(int u, int pace) {
  if (!pace) return 0;
  int v = (u + 1ll * (pace - 1) * P % Q) % Q;
  assert(bln[u] == bln[v]);
  if (pos[v] >= pos[u]) return s[v] - s[u] + buc[u];
  else return s[v] + val[bln[u]] - s[u] + buc[u];
}

void solve() {
  std::cin >> P >> Q >> n >> m >> T, T--;
  for (int i = 1; i <= n; i++) std::cin >> A[i];
  for (int i = 1; i <= m; i++) std::cin >> B[i];

  if (P > Q) std::swap(n, m), std::swap(P, Q), std::swap(A, B);
  assert(P <= Q);
  for (int i = 1; i <= m; i++) buc[B[i]] = true;

  for (int i = 0; i < Q; i++) {
    if (vis[i]) continue;
    int p = (i + P) % Q, q = i;
    vis[i] = true, bln[i] = ++cnt, pos[i] = 0;
    if (buc[i]) s[i] = 1, val[cnt] = 1;
    while (p != i) {
      vis[p] = true, bln[p] = cnt, s[p] = s[q], pos[p] = pos[q] + 1;
      if (buc[p]) s[p]++, val[cnt]++;
      q = p, p = (p + P) % Q;
    }
  }
  assert(Q % cnt == 0);
  len = Q / cnt;

  // for (int i = 0; i < Q; i++) std::cerr << s[i] << " " << buc[i] << "\n";
  // for (int i = 1; i <= cnt; i++) std::cerr << val[i] << "\n";

  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    if (T < A[i]) continue;
    i64 pace = (T - A[i]) / P + 1;
    // std::cerr << pace << "\n";
    ans += pace / len * val[bln[A[i]]] + sum(A[i], pace % len);
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
