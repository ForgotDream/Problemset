#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, q;
  std::cin >> n >> q;

  std::vector<int> a(n);
  std::vector<std::pair<int, int>> b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    b[i].first = a[i], b[i].second = i;
  }

  int block = std::sqrt(n), cnt = block;
  bool flg = (block * block == n);
  std::vector<int> lim(n, -1), L(cnt), R(cnt);
  if (flg) {
    std::sort(b.begin() + block * block, b.end());
    cnt++;
    L.push_back(block * block), R.push_back(n);
  }
  for (int i = block - 1; i >= 0; i--)  {
    L[i] = i * block, R[i] = (i + 1) * block;
    std::sort(b.begin() + L[i], b.begin() + R[i]);
    for (int j = i * block; j < (i + 1) * block; j++) {
      bool flg = false;
      for (int k = j + 1; k < (i + 1) * block; k++) {
        if (a[k] > a[j]) {
          lim[j] = k;
          flg = true;
          break;
        }
      }
      if (!flg) {
        for (int k = i + 1; k < cnt; k++) {
          int tmp = std::upper_bound(b.begin() + L[k], b.begin() + R[k], std::make_pair(a[j], j)) - b.begin();
          if (tmp == R[k]) {
            continue;
          } else {
            lim[j] = b[tmp].second;
            break;
          }
        }
        if (lim[j] == -1) {
          lim[j] = n;
        }
      }
    }
  }

  while (q--) {
    int l, r;
    std::cin >> l >> r;
    l--, r--;

    int pivot = l, ans = 0;
    
    while (pivot <= r) {
      // std::cerr << pivot << " ";
      ans++;
      if (lim[pivot] <= r) {
        ans += ((lim[pivot] - pivot) != 1);
      } else {
        ans += (pivot != r);
      }
      pivot = lim[pivot];
    }

    std::cout << ans << "\n";
  }

  return 0;
}