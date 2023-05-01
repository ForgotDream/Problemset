/**
 * @file    P6400 UMNOZAK.cpp
 * @author  ForgotDream
 * @brief   Numeric DP
 * @date    2023-05-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace Helper {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}

void debug(const std::string &s) {
  std::cerr << s << "\n";
  return;
}
}

constexpr int factorCnt[][4] = {
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 0, 1, 0, 0 },
  { 2, 0, 0, 0 },
  { 0, 0, 1, 0 },
  { 1, 1, 0, 0 },
  { 0, 0, 0, 1 },
  { 3, 0, 0, 0 },
  { 0, 2, 0, 0 },
};
constexpr int factor[] = { 2, 3, 5, 7 };

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 A, B;
  std::cin >> A >> B;

  std::vector f(19, std::vector(30, std::vector(19, std::vector(13, std::vector<i64>(11, -1)))));
  std::array<int, 4> curCnt = { 0, 0, 0, 0 };
  
  std::function<i64(int, i64, i64, i64, i64)> dfs = 
  [&](int pos, i64 lhs, i64 top, i64 l, i64 r) -> i64 {
    i64 rhs = lhs + top - 1;
    i64 &cur = f[pos][curCnt[0]][curCnt[1]][curCnt[2]][curCnt[3]];
    top /= 10;
    bool isLimited = !(lhs >= l && rhs <= r);

    if (lhs > r || rhs < l) {
      return 0;
    } else if (pos == 18) {
      return !curCnt[0] && !curCnt[1] && !curCnt[2] && !curCnt[3];
    } else if (!isLimited && cur != -1) {
      return cur;
    }

    i64 res = 0;
    for (int d = (lhs != 0); d < 10; d++) {
      bool flg = true;
      for (int i = 0; i < 4; i++) {
        if (factorCnt[d][i] <= curCnt[i]) {
          continue;
        }
        flg = false;
        break;
      } 
      if (!flg) {
        continue;
      }

      for (int i = 0; i < 4; i++) {
        curCnt[i] -= factorCnt[d][i];
      }
      res += dfs(pos + 1, lhs + d * top, top, l, r);
      // roll back changes
      for (int i = 0; i < 4; i++) {
        curCnt[i] += factorCnt[d][i];
      }
    }

    if (!isLimited) {
       cur = res;
    }
    return res;
  };

  std::function<i64(i64, int)> getNum = [&](i64 prod, int idx) -> i64 {
    if (prod > 1e9 || prod * prod > B) {
      return 0ll;
    }
    if (idx == 4) {
      return dfs(0, 0, 1e18, (A + prod - 1) / prod, B / prod);
    }

    i64 res = 0;
    // not multiply the current factor, go to the next one
    res += getNum(prod, idx + 1);
    // try to muliply the current factor
    curCnt[idx]++;
    res += getNum(prod * factor[idx], idx);
    curCnt[idx]--;

    return res;
  };

  std::cout << getNum(1, 0) << "\n";

  return 0;
}