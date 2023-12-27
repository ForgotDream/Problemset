#include <bits/stdc++.h>
using namespace std;
int n = 10, m = 20;
int p = 1000;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  srand(time(NULL));
  cout << n << " " << m << endl;
  for (int i = 1; i <= n; ++i)
    cout << rand() % p + 1 << " ";
  cout << endl;
  for (int i = 1; i <= m; ++i) {
    int op = rand() % 6 + 1;
    int l = rand() % n + 1, r = rand() % n + 1;
    int k = rand() % p;
    if (l > r)
      swap(l, r);
    switch (op) {
    case 1:
      cout << op << " " << l << " " << r << endl;
      break;
    case 2:
      cout << op << " " << l << " " << r << " " << k << endl;
      break;
    case 3:
      cout << op << " " << l << " " << r << " " << k << endl;
      break;
    case 4:
      while (r + k > n || l + k <= r) {
        l = rand() % n + 1, r = rand() % n + 1, k = rand() % p + 1;
        if (l > r)
          swap(l, r);
      }
      cout << op << " " << l << " " << r << " " << l + k << " " << r + k
           << endl;
      break;
    case 5:
      while (r + k > n || l + k <= r) {
        l = rand() % n + 1, r = rand() % n + 1, k = rand() % p + 1;
        if (l > r)
          swap(l, r);
      }
      cout << op << " " << l << " " << r << " " << l + k << " " << r + k
           << endl;
      break;
    case 6:
      cout << op << " " << l << " " << r << endl;
      break;
    }
  }
}
