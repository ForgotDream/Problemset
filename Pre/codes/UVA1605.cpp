#include <iostream>

using namespace std;

int n;
int a[100][100], b[100][100];

char c(int x) {
  if (1 <= x && x <= 26)
    return (char)'A' + (x - 1);
  else
    return (char)'a' + (x - 27);
}

int main() {
  while (cin >> n) {
    cout << 2 << " " << n << " " << n << endl;

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) a[i][j] = i, b[i][j] = j;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cout << c(a[i][j]);
      cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cout << c(b[i][j]);
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}