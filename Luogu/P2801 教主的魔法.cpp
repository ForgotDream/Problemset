/**
 * @file    P2801 教主的魔法.cpp
 * @author  ForgotDream
 * @brief   分块 or 可持久化线段树
 * @date    2023-03-02
 */
#include <bits/stdc++.h>

using i64 = long long;

template<int N>
struct SqrtBlock {
  int BLOCK, cnt;
  int n;
  std::vector<int> ed, pos, st, a, add, b;

  void init(const int &num) {
    BLOCK = std::sqrt(N);
    n = num;
    cnt = n / BLOCK + (n % BLOCK != 0);
    ed.resize(cnt + 1, 0);
    st.resize(cnt + 1, 0);
    pos.resize(N, 0);
    add.resize(cnt + 1, 0);
    for (int i = 1; i <= cnt; i++) {
      st[i] = (i - 1) * BLOCK + 1;
      ed[i] = i * BLOCK;
    }
    ed[cnt] = n;
    for (int i = 1; i <= N; i++) {
      pos[i] = (i - 1) / BLOCK + 1;
    }
    return;
  }

  SqrtBlock(const int &num) {
    init(num);
    return;
  }
  SqrtBlock(const int &num, const std::vector<int> &from) {
    init(num);
    a = from;
    b = from;
    for (int i = 1; i <= cnt; i++) {
      std::sort(b.begin() + st[i], b.begin() + ed[i] + 1);
    }
    return;
  }

  void update(int l, int r, int num) {
    int pl = pos[l], pr = pos[r];
    if (pl == pr) {
      for (int i = l; i <= r; i++) {
        a[i] += num;
      }
      for (int i = st[pl]; i <= ed[pl]; i++) {
        b[i] = a[i];
      }
      std::sort(b.begin() + st[pl], b.begin() + ed[pl] + 1);
    } else {
      for (int i = pl + 1; i < pr; i++) {
        add[i] += num;
      }
      for (int i = l; i <= ed[pl]; i++) {
        a[i] += num;
      }
      for (int i = st[pl]; i <= ed[pl]; i++) {
        b[i] = a[i];
      }
      for (int i = st[pr]; i <= r; i++) {
        a[i] += num;
      }
      for (int i = st[pr]; i <= ed[pr]; i++) {
        b[i] = a[i];
      }
      std::sort(b.begin() + st[pl], b.begin() + ed[pl] + 1);
      std::sort(b.begin() + st[pr], b.begin() + ed[pr] + 1);
    }
    return;
  }

  int query(int l, int r, int k) {
    int res = 0, pl = pos[l], pr = pos[r];
    if (pos[l] == pos[r]) {
      for (int i = l; i <= r; i++) {
        if (a[i] >= k) {
          res++;
        }
      }
    } else {
      for (int i = l; i <= ed[pl]; i++) {
        if (a[i] >= k) {
          res++;
        }
      }
      for (int i = st[pr]; i <= r; i++) {
        if (a[i] >= k) {
          res++;
        }
      }
      for (int i = pl + 1; i < pr; i++) {
        res += b.begin() + ed[i] + 1 - lower_bound(b.begin() + st[i], b.begin() + ed[i] + 1, k - add[i]);
      }
    }
    return res;
  }

};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  SqrtBlock<1000050> s(n, a);

  for (int i = 1; i <= q; i++) {
    char c;
    int l, r, val;
    std::cin >> c >> l >> r >> val;
    if (c == 'A') {
      std::cout << s.query(l, r, val) << "\n";
    } else {
      s.update(l, r, val);
    }
  }

  return 0;
}