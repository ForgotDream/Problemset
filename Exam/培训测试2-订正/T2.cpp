/**
 * @file T2.cpp
 * @author ForgotDream
 * @brief 分类讨论，大力模拟即可
 * @date 2023-01-29 
 */
 
#include <bits/stdc++.h>

using namespace std;

int n, m, sx, sy, tx, ty;
int ans;
int s1, s2, s3, s4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> sx >> sy >> tx >> ty;

    s1 = tx - 1, s2 = n - tx, s3 = ty - 1, s4 = m - ty;

    if (abs(sx - tx) + abs(sy - ty) == 1) ans = -1;
    else if (s1 <= 1 && s2 <= 1 && s3 <= 1 && s4 <= 1) ans = 1;
    else if (n <= 2 || m <= 2) ans = 2; 
    else if ((s1 <= 1 || s2 <= 1) && (s3 <= 1 || s4 <= 1)) ans = 2;
    else ans = 3;

    cout << ans << endl;
    return 0;
}