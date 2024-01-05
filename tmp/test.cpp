#include <bits/stdc++.h>
using namespace std;
const int N = 102, inf = 1e9 + 7;
int dp[N][N][1 << 8 | 2][9], gt[1 << 8], ans = inf;
int n, k, a[N], sum, tot;
int mx(int x, int y) { return x > y ? x : y; }
int mi(int x, int y) { return x < y ? x : y; }
void init() {
  ans = inf;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= k; j++)
      for (int k = 0; k < (1 << 8); k++)
        for (int s = 0; s <= 8; s++)
          dp[i][j][k][s] = inf;
}
int main() {
  for (int i = 0; i < (1 << 8); i++) {
    for (int j = 7; j >= 0; j--)
      if ((i >> j) & 1)
        gt[i]++; // 提前预处理出每种状态的选出来的个数
  }
  while (1) {
    scanf("%d%d", &n, &k);
    sum = 0; // 总状态
    if (!n && !k)
      break;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), a[i] -= 25, sum |= (1 << a[i]);
    init(); // 初始化
    dp[1][0][1 << a[1]][a[1]] = 1;
    dp[1][1][0][8] = 0;
    for (int i = 1; i < n; i++)
      for (int j = 0; j <= k; j++)
        for (int k = 0; k < (1 << 8); k++)
          for (int s = 0; s <= 8; s++) {
            if (dp[i][j][k][s] == inf)
              continue;
            dp[i + 1][j][k | (1 << a[i + 1])][a[i + 1]] =
                mi(dp[i + 1][j][k | (1 << a[i + 1])][a[i + 1]],
                   dp[i][j][k][s] + (a[i + 1] == s ? 0 : 1));
            dp[i + 1][j + 1][k][s] = mi(dp[i + 1][j + 1][k][s], dp[i][j][k][s]);
          }
    for (int i = 0; i <= k; i++)
      for (int j = 0; j < (1 << 8); j++)
        for (int k = 0; k <= 7; k++) {
          if (dp[n][i][j][k] == inf)
            continue;
          ans = mi(
              ans,
              dp[n][i][j][k] +
                  gt[sum ^
                     j]); // sum为总种类，j为当前情况下序列中未被抽出的数的种类，那么sum^j就是全部抽出来的数的种类，这些数不管放哪里混乱度都会+1
        }
    printf("Case %d: %d\n\n", ++tot, ans);
  }
  return 0;
}
