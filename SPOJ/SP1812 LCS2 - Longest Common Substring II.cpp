/*
 * @file    SP1812 LCS2 - Longest Common Substring II.cpp
 * @author  ForgotDream
 * @brief   GSAM
 * @date    2024-01-21
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 15, M = 1e5 + 50;

int n;
std::string s[N];

struct GSAM {
  int len[2 * N * M], link[2 * N * M], cnt = 1;
  int ch[2 * N * M][26];

  int expand(int lst, int d) {
    int p = lst;
    if (int q = ch[p][d]) {
      if (len[p] + 1 == len[q]) {
        return q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[q] = tmp;
        return tmp;
      }
    }
    int cur = ++cnt;
    len[cur] = len[p] + 1;
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
    return cur;
  }

  int tag[2 * N * M], siz[2 * N * M];

  int calc() {
    int res = 0;
    for (int i = 1; i < n; i++) {
      int p = 1;
      for (auto c : s[i]) {
        int d = c - 'a';
        p = ch[p][d];
        for (int t = p; tag[t] != i; t = link[t]) tag[t] = i, siz[t]++;
      }
    }
    for (int i = 1; i <= cnt; i++) {
      if (siz[i] == n - 1) res = std::max(res, len[i]);
    }
    return res;
  }
} gsam;

void solve() {
  while (std::cin >> s[++n]) {
    int lst = 1;
    for (auto c : s[n]) lst = gsam.expand(lst, c - 'a');
  }
  std::cout << gsam.calc() << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
