#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int n, m, a[(int)2e6 + 50];
int q[(int)2e6 + 50];

inline int read() {
  int x = 0, t = 1;
  char ch = getchar();  // 读入单个字符到寄存器
  while (ch < '0' || ch > '9') {
    if (ch == '-') t = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * t;
}

inline void write(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
}

void solve() {
  int head = 0, tail = 0;
  a[0] = 0x3f3f3f3f;
  write(0), putchar('\n');
  // cout << 0;
  for (int i = 1; i < m; i++) {
    while (head <= tail && a[q[tail]] >= a[i]) tail--;
    q[++tail] = i;
    write(a[q[head]]), putchar('\n');
  }
  for (int i = m; i <= n; i++) {
    while (head <= tail && a[q[tail]] >= a[i]) tail--;
    q[++tail] = i;
    while (q[head] <= i - m) head++;
    if (i != n) write(a[q[head]]), putchar('\n');
  }
  cout << endl;
  return;
}

int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  solve();
  return 0;
}