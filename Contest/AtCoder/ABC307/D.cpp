#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::string s;
  std::cin >> n >> s;

  std::stack<int> st;
  std::vector<int> d(n);
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      st.push(i);
    } else if (s[i] == ')') {
      if (!st.empty()) {
        int l = st.top();
        d[l]++; 
        if (i != n - 1) {
          d[i + 1]--;
        }
        st.pop();
      }
    }
  }

  std::partial_sum(d.begin(), d.end(), d.begin());

  for (int i = 0; i < n; i++) {
    if (!d[i]) {
      std::cout << s[i];
    }
  }
  std::cout << "\n";

  return 0;
}