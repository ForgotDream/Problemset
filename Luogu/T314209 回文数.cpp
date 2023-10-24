/**
 * @file    T314209 回文数.cpp
 * @author  ForgotDream
 * @brief   数位 DP
 * @date    2023-02-28
 */
#include <bits/stdc++.h>

using i64 = long long;

int f[25][25][2];
int tmp[25];
std::vector<int> nums;

i64 dfs(int pos, int cur, bool isPalin, bool isLimited) {
  if (!cur) {
    return isPalin;
  } 
  if (!isLimited && f[pos][cur][isPalin] != -1) {
    return f[pos][cur][isPalin];
  }
  int up = isLimited ? nums[cur] : 9;
  i64 res = 0;
  for (int i = 0; i <= up; i++) {
    tmp[cur] = i;
    if (pos == cur && i == 0) {
      res += dfs(pos - 1, cur - 1, isPalin, isLimited && i == nums[cur]);
    } else if (isPalin && cur <= (pos + 1) / 2) {
      res += dfs(pos, cur - 1, tmp[pos - cur + 1] == i, isLimited && i == nums[cur]);
    } else {
      res += dfs(pos, cur - 1, isPalin, isLimited && i == nums[cur]);
    }
  }
  if (!isLimited) {
    f[pos][cur][isPalin] = res;
  }
  return res;
}

i64 calc(i64 num) {
  nums.resize(1, 0);
  while (num) {
    nums.push_back(num % 10);
    num /= 10;
  }
  return dfs(nums.size() - 1, nums.size() - 1, true, true);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(f, -1, sizeof(f));

  i64 l, r;
  std::cin >> l >> r;
  std::cout << calc(r) - calc(l - 1) << "\n";

  return 0;
}