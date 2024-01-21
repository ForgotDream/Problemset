/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-01-21
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

std::string s, t;

struct SAM {
  int ch[N][26], len[N], link[N], siz[N], lst = 1, cnt = 1;

  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1, siz[cur]++;
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

std::vector<int> adj[N];

void solve() {
  std::cin >> s >> t;
  for (auto c : s) sam.expand(c - 'a');

  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
