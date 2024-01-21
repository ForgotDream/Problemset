/*
 * @file    P2178 [NOI2015] 品酒大会.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;

int cnt[N];

struct SAM {
  int ch[N][26], len[N], link[N], cnt = 1, lst = 1;
  int expand(char c) {
    int cur = ++cnt, d = c - 'a';
    len[cur] = len[lst] + 1, ::cnt[cur] = 1;
    int p = lst;
    for (; p && !ch[p][d]; p = link[p]) ch[p][d] = cur;
    if (!p) {
      link[cur] = 1;
    } else {
      int q = ch[p][d];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

int n, a[N];
char s[N];

std::vector<int> adj[N];
i64 sum[N];
int mx[N], smx[N], mn[N], smn[N];  // `s` stands for `semi`

i64 ans[N];

inline void chkmax(int u, int w) {
  if (w >= mx[u]) smx[u] = mx[u], mx[u] = w;
  else if (w > smx[u]) smx[u] = w;
}
inline void chkmin(int u, int w) {
  if (w <= mn[u]) smn[u] = mn[u], mn[u] = w;
  else if (w < smn[u]) smn[u] = w;
}

void dfs(int u) {
  int t = 0;
  for (auto v : adj[u]) {
    dfs(v), t += cnt[v];
    chkmax(u, mx[v]), chkmax(u, smx[v]);
    chkmin(u, mn[v]), chkmin(u, smn[v]);
  }
  if (t + cnt[u] < 2) return cnt[u] += t, void();
  i64 &p = ans[sam.len[u]];
  p = std::max({p, 1ll * mx[u] * smx[u], 1ll * mn[u] * smn[u]});
  for (auto v : adj[u]) {
    sum[sam.len[u]] += 1ll * cnt[u] * cnt[v];
    cnt[u] += cnt[v];
  }
}

void solve() {
  memset(mx, -0x3f, sizeof(mx)), memset(smx, -0x3f, sizeof(mx));
  memset(mn, 0x3f, sizeof(mn)), memset(smn, 0x3f, sizeof(mn));
  memset(ans, -0x3f, sizeof(ans));
  
  std::cin >> n >> (s + 1);
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  for (int i = n; i >= 1; i--) {
    int p = sam.expand(s[i]);
    mx[p] = mn[p] = a[i];
  }
  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);

  dfs(1);
  for (int i = n - 1; ~i; i--) {
    sum[i] += sum[i + 1];
    ans[i] = std::max(ans[i], ans[i + 1]);
  }
  for (int i = 0; i < n; i++) {
    std::cout << sum[i] << " " << (sum[i] ? ans[i] : 0) << "\n";
  }
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  
  return 0;
}
