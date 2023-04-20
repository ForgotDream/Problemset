/**
 * @file    P1074 靶形数独.cpp
 * @author  ForgotDream
 * @brief   DLX
 * @date    2023-03-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

// The expected scores of each position in the Sodoku
static const std::vector<std::vector<int>> score = {
  {6, 6, 6, 6, 6, 6, 6, 6, 6},
  {6, 7, 7, 7, 7, 7, 7, 7, 6},
  {6, 7, 8, 8, 8, 8, 8, 7, 6},
  {6, 7, 8, 9, 9, 9, 8, 7, 6},
  {6, 7, 8, 9, 10, 9, 8, 7, 6},
  {6, 7, 8, 9, 9, 9, 8, 7, 6},
  {6, 7, 8, 8, 8, 8, 8, 7, 6},
  {6, 7, 7, 7, 7, 7, 7, 7, 6},
  {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

int calc(int r, int c, int val) {
  return score[r][c] * val;
}

// use DLX to solve this problem
struct DLX {
  static const int MAX = 1e5 + 10;
  int n, m, cnt;
  std::vector<int> L, R, U, D;
  std::vector<int> first, col, row, siz, stk;

  DLX(int n, int m) {
    this->n = n;
    this->m = m;
    L.resize(MAX), R.resize(MAX);
    U.resize(MAX), D.resize(MAX);
    first.resize(MAX, 0);
    col.resize(MAX), row.resize(MAX);
    siz.resize(MAX, 0), stk.resize(MAX);
    build(n, m);
    return;
  }

  void build(int r, int c) {
    for (int i = 0; i <= c; i++) {
      L[i] = i - 1, R[i] = i + 1;
      U[i] = D[i] = i;
    }
    L[0] = c, R[c] = 0;
    cnt = c;
    return;
  }

  void insert(int r, int c) {
    col[++cnt] = c, row[cnt] = r;
    siz[c]++;
    D[cnt] = D[c], U[D[c]] = cnt;
    U[cnt] = c, D[c] = cnt;

    if (!first[r]) {
      first[r] = L[cnt] = R[cnt] = cnt;
    } else {
      R[cnt] = R[first[r]], L[R[first[r]]] = cnt;
      L[cnt] = first[r], R[first[r]] = cnt;
    }

    return;
  }

  void remove(int c) {
    L[R[c]] = L[c], R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
      for (int j = R[i]; j != i; j = R[j]) {
        U[D[j]] = U[j], D[U[j]] = D[j];
        siz[col[j]]--;
      }
    }
    return;
  }

  void recover(int c) {
    for (int i = U[c]; i != c; i = U[i]) {
      for (int j = L[i]; j != i; j = L[j]) {
        U[D[j]] = D[U[j]] = j;
        siz[col[j]]++;
      }
    }
    L[R[c]] = R[L[c]] = c;
    return;
  }

  void dance(int dep, int &ans) {
    if (!R[0]) {
      int cur = 0;
      for (int i = 1; i < dep; i++) {
        int r = (stk[i] - 1) / 9 / 9;
        int c = (stk[i] - 1) / 9 % 9;
        int val = (stk[i] - 1) % 9 + 1;
        cur += calc(r, c, val);
      }
      ans = std::max(ans, cur);
      return;
    }

    int c = R[0];
    for (int i = R[0]; i != 0; i = R[i]) {
      if (siz[i] < siz[c]) {
        c = i;
      }
    }
    remove(c);

    for (int i = D[c]; i != c; i = D[i]) {
      stk[dep] = row[i];
      for (int j = R[i]; j != i; j = R[j]) {
        remove(col[j]);
      }
      dance(dep + 1, ans);
      for (int j = L[i]; j != i; j = L[j]) {
        recover(col[j]);
      }
    }
    recover(c);

    return;
  }
};

void insert(int r, int c, int val, DLX &dlx) {
  int dx = r / 3 + 1, dy = c / 3 + 1, slot = (dx - 1) * 3 + dy;
  int no = 9 * 9 * r + 9 * c + val;
  
  int f1 = 9 * r + val;
  int f2 = 81 + 9 * c + val;
  int f3 = 81 * 2 + 9 * (slot - 1) + val;
  int f4 = 81 * 3 + 9 * r + c + 1;

  dlx.insert(no, f1);
  dlx.insert(no, f2);
  dlx.insert(no, f3);
  dlx.insert(no, f4);

  return;
}

signed main() {
  #ifndef DONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  DLX dlx(729, 324);

  std::vector<std::vector<int>> a(9, std::vector<int>(9));
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      // std::cerr << i << " " << j << "\n";
      std::cin >> a[i][j];
      for (int k = 1; k <= 9; k++) {
        if (a[i][j] && k != a[i][j]) {
          continue;
        }
        insert(i, j, k, dlx);
      }
    }
  }

  int ans = -0x3f3f3f3f;
  dlx.dance(1, ans);

  std::cout << ((ans == -0x3f3f3f3f) ? -1 : ans) << "\n";

  return 0;
}