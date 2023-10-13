#include <bits/stdc++.h>
#define ll long long
#define maxn 3000005
#define mod 998244353
using namespace std;
ll C[3005][3005];
void init() {
  C[0][0] = 1;
  for (int i = 1; i <= 3000; i++)
    for (int j = 0; j <= i; j++) {
      if (i == 1 || j == 0)
        C[i][j] = 1;
      else
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
}
int n, m;
int a[21];
int premax[1 << 20];
void init2() {
  for (int sta = 0; sta < (1 << n); sta++) {
    for (int i = 0; i < n; i++)
      if ((sta >> i) & 1) premax[sta] = max(premax[sta], a[i]);
  }
}
int dp[2][22][1 << 20];
ll ans[25];
void add(int &x, int y) {
  x = (x + y) % mod;
  return;
}
void DP() {
  int now = 0, nxt = 1;
  dp[now][n - 1][0] = 1;
  for (int turn = 1; turn <= n; turn++) {
    for (int i = n - 1; i >= 0; i--)
      for (int sta = 0; sta < (1 << n); sta++)
        if (dp[now][i][sta]) {
          int tmp = dp[now][i][sta];
          // case1：不选
          if (i)
            add(dp[now][i - 1][sta], tmp);
          else
            add(dp[nxt][n - 1][sta], tmp);
          // case2：选
          if (((sta >> i) & 1) == 0 &&
              premax[sta & ((1 << i) - 1)] + 1 == a[i]) {
            if (i)
              add(dp[now][i - 1][sta | (1 << i)], tmp);
            else
              add(dp[nxt][n - 1][sta | (1 << i)], tmp);
          }
          dp[now][i][sta] = 0;
        }
    // 此时dp[nxt][n-1][sta]就是选了最多turn个数的时候的方案数
    ans[turn] = dp[nxt][n - 1][(1 << n) - 1];
    swap(now, nxt);
  }
  ll tot = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 1; j--) {
      ans[i] = (ans[i] + (-1 * C[i][j] * ans[j] % mod) + mod) % mod;
    }
    tot = (tot + ans[i] * C[m][i] % mod) % mod;
  }
  cout << tot << endl;
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  init();
  init2();
  DP();
}
