#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 30000 + 10;
const int MAXP = 710;

int a[MAXN], f[MAXN][MAXP];
int n, d;

inline int getnum() {
    int ans = 0; char c; bool flag = false;
    while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
    if (c == '-') flag = true; else ans = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ans = ans * 10 + c - '0';
    return ans * (flag ? -1 : 1);
}
int main() { 
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
    n = getnum(); d = getnum(); int tar = 0;
    for (int i = 1; i <= n; i++) { int x = getnum(); a[x]++; tar = max(tar, x); }
    for (int i = tar; i >= d; i--)
        for (int j = 0; j <= 700; j++) { int p = j - 350;
            if (d + p <= 0) continue;
            f[i][j] = a[i];
            if (i + d + p <= tar) {
                f[i][j] += max(f[i + d + p][j], max(f[i + d + p][j - 1], f[i + d + p][j + 1]));
            }
        }
    int ans = max(f[d][350], max(f[d][351], f[d][349]));
    printf("%d\n", ans);
}
