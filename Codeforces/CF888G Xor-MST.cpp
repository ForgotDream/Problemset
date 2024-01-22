/*
 * @file    CF888G Xor-MST.cpp
 * @author  ForgotDream
 * @brief   Trie + Boruvka
 * @date    2024-01-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

int n, a[N];

int L[N << 5], R[N << 5], ch[N << 5][2], cnt;

void insert(int num, int id) {
  int p = 0;
  for (int i = 30; i >= 0; i--) {
    int d = num >> i & 1;
    if (!ch[p][d]) ch[p][d] = ++cnt;
    p = ch[p][d], R[p] = id;
    if (!L[p]) L[p] = id;
  }
}

int query(int u, int num, int dep) {
  int p = u, res = 0;
  for (int i = dep; i >= 0; i--) {
    int d = num >> i & 1;
    if (ch[p][d]) p = ch[p][d];
    else p = ch[p][d ^ 1], res += 1 << i;
  }
  return res;
}

i64 dfs(int u, int dep) {
  if (dep == -1) return 0;
  if (ch[u][0] && ch[u][1]) {
    int ans = 1 << 30;
    for (int i = L[ch[u][0]]; i <= R[ch[u][0]]; i++) {
      ans = std::min(ans, query(ch[u][1], a[i], dep - 1) + (1 << dep));
    }
    return ans + dfs(ch[u][0], dep - 1) + dfs(ch[u][1], dep - 1);
  } else if (ch[u][0]) {
    return dfs(ch[u][0], dep - 1);
  } else if (ch[u][1]) {
    return dfs(ch[u][1], dep - 1);
  } else {
    return 0;
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) insert(a[i], i);

  std::cout << dfs(0, 30) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
