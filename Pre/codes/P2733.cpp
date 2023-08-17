#include <cstdio>
#include <iostream>

using namespace std;

int n;
char c;
bool mat[255][255];
int f[255][255][255];

void solve() {
  for (int i = 2; i <= n; i++) {
    int sum = 0;
    for (int j = 1; j <= n - i + 2; j++) {
      for (int k = 1; k <= n - i + 2; k++) {
        if (!mat[j][k])
          mat[j - 1][k - 1] = 0, mat[j - 1][k] = 0, mat[j][k - 1] = 0;
        sum += mat[j - 1][k - 1];
      }
    }
    if (sum != 0) cout << i << " " << sum << endl;
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) cin >> c, mat[i][j] = (c == '1');
  solve();
  return 0;
}