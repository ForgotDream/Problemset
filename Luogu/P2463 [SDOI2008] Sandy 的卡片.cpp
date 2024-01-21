/*
 * @file    P2463 [SDOI2008] Sandy 的卡片.cpp
 * @author  ForgotDream
 * @brief   SAM
 * @date    2024-01-21
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1050, M = 105;

int n;
int a[N][M], m[N];

struct GSAM {
  int len[2 * N * M], link[2 * N * M], cnt = 1;
  std::map<int, int> ch[2 * N * M];

int expand(int lst, int d) {
    int p = lst;
    if (int q = ch[p][d]) {
      if (len[p] + 1 == len[q]) {
        return q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q], ch[tmp] = ch[q];
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
        len[tmp] = len[p] + 1, link[tmp] = link[q], ch[tmp] = ch[q];
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return cur;
  }

  int tag[2 * N * M], siz[2 * N * M];

  int calc() {
    int res = 1;
    for (int i = 1; i <= n; i++) {
      int p = 1;
      for (int j = 2; j <= m[i]; j++) {
        p = ch[p][a[i][j]];
        for (int t = p; tag[t] != i; t = link[t]) tag[t] = i, siz[t]++;
      }
    }
    for (int i = 1; i <= cnt; i++) {
      if (siz[i] == n) res = std::max(res, len[i] + 1);
    }
    return res;
  }
} gsam;

void solve() {
  std::cin >> n;
  for (int i = 1, lst = 1; i <= n; i++, lst = 1) {
    std::cin >> m[i];
    for (int j = 1; j <= m[i]; j++) std::cin >> a[i][j];
    for (int j = m[i]; j >= 2; j--) a[i][j] = a[i][j] - a[i][j - 1];

    for (int j = 2; j <= m[i]; j++) lst = gsam.expand(lst, a[i][j]);
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
