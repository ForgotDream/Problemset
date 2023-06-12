/**
 * @file    P4484 最长上升子序列.cpp
 * @author  ForgotDream
 * @brief   打表
 * @date    2023-06-12
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int ans[] = {
  0,
  1,
  499122178,
  2,
  915057326,
  540715694,
  946945688,
  422867403,
  451091574,
  317868537,
  200489273,
  976705134,
  705376344,
  662845575,
  331522185,
  228644314,
  262819964,
  686801362,
  495111839,
  947040129,
  414835038,
  696340671,
  749077581,
  301075008,
  314644758,
  102117126,
  819818153,
  273498600,
  267588741
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::cout << ans[n] << "\n";

  return 0;
}