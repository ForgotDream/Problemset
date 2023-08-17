#include <cstring>
#include <iostream>

using namespace std;

int n, a[25], ans = -1;
bool mat[25][25];
int f[25];
int path[25], res[25];

void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (mat[i][j]) {
        if (f[j] + a[i] > f[i]) f[i] = f[j] + a[i], path[i] = j;
      }
    }
  }
  int flag = 0, cnt = 0;
  for (int i = 1; i <= n; i++)
    if (ans < f[i]) ans = f[i], flag = i;
  res[0] = flag;
  while (flag != 0) {
    res[++cnt] = path[flag];
    flag = path[flag];
  }
  for (int i = cnt - 1; i >= 0; i--) cout << res[i] << " ";
  cout << endl << ans << endl;
  return;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], f[i] = a[i];
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) cin >> mat[j][i], mat[i][j] = mat[j][i];
  solve();
  return 0;
}