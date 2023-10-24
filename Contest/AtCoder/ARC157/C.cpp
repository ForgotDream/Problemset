#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 2e3 + 50;
static const i128 MOD = 998244353;
int h, w;
int a[N][N];
i128 C[2 * N][2 * N], ans;
i128 lenSum[N][N], lenPow[N][N];

void getC(int n) {
  for (int i = 0; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
  }
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  getC(4e3);

  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      char c;
      cin >> c;
      a[i][j] = (c == 'Y');
    }
  }

  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      (lenSum[i][j] = lenSum[i - 1][j] + lenSum[i][j - 1]) %= MOD;
      (lenPow[i][j] = lenPow[i - 1][j] + lenPow[i][j - 1]) %= MOD;
      if (!a[i][j]) {
        continue;
      }
      if (a[i - 1][j]) {
        (lenPow[i][j] = lenPow[i - 1][j] + 2 * lenSum[i - 1][j] + C[(i - 1) + j - 2][i - 1]) %= MOD;
        (lenSum[i][j] = lenSum[i - 1][j] + C[(i - 1) + j - 2][i - 1]) %= MOD;
      }
    }
  }

  cout << (i64) ans << '\n';

  return 0;
}