#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cout << a + b << '\n';
    }
    return 0;
}