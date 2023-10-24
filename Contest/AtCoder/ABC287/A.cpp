#include <bits/stdc++.h>

using namespace std;

int n;
string str;
int ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> str, ans += (str == "For");

    if (ans * 2 < n) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}