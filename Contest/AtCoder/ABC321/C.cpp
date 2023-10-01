#include <iostream>

using i64 = long long;

i64 K;
i64 dp[15][15];
int main() {
  for (int i = 0; i <= 9; i++) dp[1][i] = 1;
  for (int i = 2; i <= 10; i++)
    for (int j = i - 1; j <= 9; j++)
      for (int k = j - 1; k >= 0; k--) dp[i][j] += dp[i - 1][k];
  std::cin >> K;
  K++;
  i64 pos = 0, ans = 0;
  i64 pre = 0;
  for (int i = 1; i <= 10; i++) {
    for (int j = 0; j <= 9; j++) {
      if (pre < K && K <= pre + dp[i][j]) {
        ans = j, pos = i, K -= pre;
        goto end;
      }
      pre += dp[i][j];
    }
  }
end:
  pre = ans;
  for (int i = pos - 1; i >= 1; i--) {
    i64 temp = 0;
    for (int j = 0; j < pre; j++) {
      if (K > dp[i][j])
        K -= dp[i][j];
      else {
        ans = ans * 10 + j;
        pre = j;
        break;
      }
    }
  }
  std::cout << ans << "\n";
  return 0;
}
