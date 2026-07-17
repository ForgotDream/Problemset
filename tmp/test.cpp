#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;
    string s;
    cin >> s;

    // If we can delete all characters or more, just output all 1s (capped at n).
    if (k >= n) {
        cout << string(n, '1') << "\n";
        return;
    }

    // P[i] = count of '(' in s[0...i-1]
    vector<int> P(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        P[i + 1] = P[i] + (s[i] == '(' ? 1 : 0);
    }

    // S[i] = count of ')' in s[i...n-1]
    vector<int> S(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        S[i] = S[i + 1] + (s[i] == ')' ? 1 : 0);
    }

    int min_x = max(0, k - S[0]);
    int max_x = min(k, P[n]);

    int min_val = 2e9;
    int best_x = min_x;

    // Find the absolute minimum in the 2D search space in O(n)
    for (int i = 0; i <= n; ++i) {
        int cands[] = {min_x, max_x, P[i], k - S[i]};
        for (int x : cands) {
            if (x >= min_x && x <= max_x) {
                int val = max(0, P[i] - x) + max(0, S[i] - (k - x));
                if (val < min_val) {
                    min_val = val;
                    best_x = x;
                }
            }
        }
    }

    int x = best_x;
    int y = k - best_x;

    // Greedily mark the first 'x' open brackets and the last 'y' close brackets
    string ans(n, '0');
    int marked_x = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(' && marked_x < x) {
            ans[i] = '1';
            marked_x++;
        }
    }

    int marked_y = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == ')' && marked_y < y) {
            ans[i] = '1';
            marked_y++;
        }
    }

    cout << ans << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
