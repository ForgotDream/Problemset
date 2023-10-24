/**
 * @file    P1731 生日蛋糕.cpp
 * @author  ForgotDream
 * @brief   搜索 + 剪枝
 * @date    2023-03-27
 */
#include <bits/stdc++.h>
#include <ctime>

using i64 = long long;
using f80 = long double;

std::pair<std::vector<int>, std::vector<int>> pre(int tgt) {
  std::vector<int> res1, res2;
  for (int i = 0; i < tgt; i++) {
    res1.push_back((tgt - i) * (tgt - i) * (tgt - i));
    res2.push_back(2 * (tgt - i) * (tgt - i));
  }
  for (int i = tgt - 1; ~i; i--) {
    if (i != tgt - 1) {
      res1[i] += res1[i + 1];
      res2[i] += res2[i + 1];
    }
  }
  return std::make_pair(res1, res2);
}

int ans = 0x3f3f3f3f;
std::vector<int> rstV, rstS;
void solve(int cur, int tgt, int rst, int curAns, int lstH, int lstR) {
  if (cur == 1) {
    auto i = pre(tgt);
    rstV = i.first;
    rstS = i.second;
  }
  if (cur == tgt + 1) {
    if (rst) {
      return;
    }
    ans = std::min(ans, curAns);
    return;
  } else if (rst <= 0) {
    return;
  } else if (curAns + rstS[cur - 1] > ans) {
    return;
  } else if (rst < rstV[cur - 1]) {
    return;
  } else if (cur != 1 && curAns + 2 * rst / std::max(1, lstR - 1) > ans) {
    return;
  }

  int maxr = (cur == 1 ? std::sqrt(rst) : lstR - 1);
  for (int i = maxr; i; i--) {
    int maxh = (cur == 1 ? rst / (i * i) : std::min(rst / (i * i), lstH - 1));
    for (int j = maxh; j; j--) {
      if (i * i * j * (tgt - cur + 1) < rst) {
        continue;
      } else if (i * i * j > rst) {
        continue;
      } else if (cur + 2 * rst / std::max(i - 1, 1) > ans) {
        continue;
      }
      solve(cur + 1, tgt, rst - i * i * j, curAns + 2 * i * j + ((cur == 1) ? (i * i) : 0), j, i);
    }
  }

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  solve(1, m, n, 0, 0, 0);
  
  if (ans == 0x3f3f3f3f) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }

  return 0;
}