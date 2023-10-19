#include <bits/stdc++.h>
#define rep(q, a, b) for (int q = a, q##_end_ = b; q <= q##_end_; ++q)
#define dep(q, a, b) for (int q = a, q##_end_ = b; q >= q##_end_; --q)
#define mem(a, b) memset(a, b, sizeof a)
#define debug(a) cerr << #a << ' ' << a << "___" << endl
using namespace std;
void in(int &r) {
  static char c;
  r = 0;
  while (c = getchar(), !isdigit(c))
    ;
  do r = (r << 1) + (r << 3) + (c ^ 48);
  while (c = getchar(), isdigit(c));
}
const int mn = 2005;
int dp[mn][mn * 3][2];
int had[mn][4], n;  // 其实这里had是没有的意思，没有改过来
const int mod = 1e9 + 7;
int mul[mn * 3], inv[mn * 3];
int C(int a, int b) { return 1LL * mul[b] * inv[a] % mod * inv[b - a] % mod; }
int A(int a, int b) { return 1LL * mul[b] * inv[b - a] % mod; }
int tot_sum, ans = 1;
void add(int &a, long long b) { a = (a + b) % mod; }
int Sum[mn * 3][2];
void get_ans(int l, int r) {
  if (l > r) return;
  int sum = 0;
  int v = had[l][1] + had[l][3];
  dp[l][v + 1][0] = A(v, v);
  rep(q, 1, v) dp[l][q][1] = A(v, v);
  sum += v + 1;

  rep(q, l + 1, r) {
    v = had[q][1] + had[q][3];
    rep(w, 1, sum) Sum[w][0] = dp[q - 1][w][0], Sum[w][1] = dp[q - 1][w][1];
    rep(w, 1, sum) add(Sum[w][0], Sum[w - 1][0]), add(Sum[w][1], Sum[w - 1][1]);
    rep(w, v + 1, sum + v + 1) {
      add(dp[q][w][0], 1LL * A(v, w - 1) * Sum[sum][0]);
    }
    rep(w, v + 1, sum + v) {
      add(dp[q][w][0], 1LL * A(v, w - 1) * (Sum[sum][1] - Sum[w - v - 1][1]));
    }
    rep(r, 0, v - 1) {
      int ty = C(r, v);
      rep(w, r + 1, sum + r + 1) {
        add(dp[q][w][1], 1LL * ty * A(r, w - 1) * A(v - r, sum + v + 1 - w) %
                             mod * Sum[w - r - 1][0]);
      }
    }
    sum += v + 1;
  }

  int tot = 0;
  rep(q, 0, sum) {
    add(tot, dp[r][q][0]);
    add(tot, dp[r][q][1]);
  }
  tot_sum += sum, ans = 1LL * ans * tot % mod * C(sum, tot_sum) % mod;
}
bool check_it_can_be_solve() {
  if (had[1][1] || had[1][3] || had[n][1] || had[n][3]) return 0;
  rep(q, 2,
      n) if (had[q][1] && had[q - 1][1] || had[q][3] && had[q - 1][3]) return 0;
  return 1;
}
char as[mn];
int main() {
  in(n);
  mul[0] = 1;
  rep(q, 1, n * 3) mul[q] = 1LL * mul[q - 1] * q % mod;
  inv[0] = inv[1] = 1;
  rep(q, 2, n * 3) inv[q] = 1LL * (mod - mod / q) * inv[mod % q] % mod;
  rep(q, 1, n * 3) inv[q] = 1LL * inv[q - 1] * inv[q] % mod;
  rep(q, 1, 3) {
    scanf("%s", as + 1);
    rep(w, 1, n) had[w][q] = as[w] == 'x';
  }
  if (!check_it_can_be_solve()) {
    puts("0");
    return 0;
  }
  int now = 1;
  while (now <= n && had[now][2]) ++now;
  if (now == n + 1)
    get_ans(1, now - 1);
  else {
    get_ans(1, now - 1);
    int v = had[now][1] + had[now][3];
    tot_sum += v, ans = 1LL * ans * A(v, tot_sum) % mod;
    ++now;
    while (1) {
      int last = now;
      while (now <= n && had[now][2]) ++now;
      if (now == n + 1)
        get_ans(last, now - 1);
      else {
        get_ans(last, now - 1);
        v = had[now][1] + had[now][3];
        tot_sum += v, ans = 1LL * ans * A(v, tot_sum) % mod;
        ++now;
      }
      if (now == n + 1) break;
    }
  }
  printf("%d\n", (ans + mod) % mod);
  return 0;
}
