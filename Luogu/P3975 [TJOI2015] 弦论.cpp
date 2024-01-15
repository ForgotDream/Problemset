/*
 * @file    P3975 [TJOI2015] 弦论.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50;

i64 siz[N], sum[N];

struct SAM {
  int ch[N][26], link[N], len[N], cnt, lst;
  void init() { link[0] = -1, len[0] = cnt = lst = 0; }
  void expand(char c) {
    int cur = ++cnt, d = c - 'a';
    len[cur] = len[lst] + 1, siz[cur] = 1;
    int p = lst;
    for (; ~p && !ch[p][d]; p = link[p]) ch[p][d] = cur;
    if (p == -1) return link[cur] = 0, lst = cur, void();
    int q = ch[p][d];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
    } else {
      int tmp = ++cnt;
      len[tmp] = len[p] + 1, link[tmp] = link[q];
      memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
      for (; ~p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
      link[cur] = link[q] = tmp;
    }
    lst = cur;
  }
  void build(const std::string_view &s) {
    init();
    for (auto c : s) expand(c);
  }
} sam;

std::string s;
int t;
i64 k;

int b[N], p[N];

void traverse(int u) {
  if (k <= siz[u]) return;
  k -= siz[u];
  for (int i = 0; i < 26; i++) {
    int v = sam.ch[u][i];
    if (!v) continue;
    if (k > sum[v]) {
      k -= sum[v];
      continue;
    }
    std::cout.put(i + 'a'), traverse(v);
    return;
  }
}

void solve() {
  std::cin >> s >> t >> k;
  sam.build(s);

  // Topo
  for (int i = 0; i <= sam.cnt; i++) b[sam.len[i]]++;
  // for (int i = 0; i <= sam.cnt; i++) std::cerr << b[i] << "\n";
  for (int i = 1; i <= sam.cnt; i++) b[i] += b[i - 1];
  for (int i = 1; i <= sam.cnt; i++) p[b[sam.len[i]]--] = i;

  for (int i = sam.cnt + 1; i >= 1; i--) siz[sam.link[p[i]]] += siz[p[i]];
  for (int i = 0; i <= sam.cnt; i++) {
    if (t) sum[i] = siz[i];
    else sum[i] = siz[i] = 1;
  }
  siz[0] = sum[0] = 0;

  for (int i = sam.cnt + 1; i >= 1; i--) {
    for (int j = 0; j < 26; j++) {
      if (!sam.ch[p[i]][j]) continue; 
      sum[p[i]] += sum[sam.ch[p[i]][j]];
    }
  }

  if (sum[0] < k) return std::cout << -1 << "\n", void();
  traverse(0);
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
