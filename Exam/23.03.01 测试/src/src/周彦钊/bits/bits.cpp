#include <bits/stdc++.h>

using i64 = long long;

static const int N = 60;
i64 f[N][2][N];
i64 n, L, I;
int nums[N], len;

i64 dfs(int pos, int cur, int all, bool isLimited) {
  if (all > L) {
    return 0;
  }
  if (!pos) {
    return all <= L;
  }
  if (!isLimited && ~f[pos][cur][all]) {
    return f[pos][cur][all];
  }
  int up = isLimited ? nums[pos] : 1;
  i64 res = 0;
  for (int i = 0; i <= up; i++) {
    res += dfs(pos - 1, i, all + (i == 1), isLimited && i == up);
  }
  if (!isLimited) {
    f[pos][cur][all] = res;
  }
  return res;
}

i64 calc(i64 mid) {
  if (mid == 0) {
    return 1;
  }
  len = 0;
  i64 res = 0;
  while (mid) {
    nums[++len] = mid & 1;
    mid >>= 1;
  }
  for (int i = 0; i <= nums[len]; i++) {
    res += dfs(len - 1, i, i == 1, i == nums[len]);
  }
  return res;
}

int main() {
  // freopen("bits.in", "r", stdin);
  // freopen("bits.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  memset(f, -1, sizeof(f));
  
  std::cin >> n >> L >> I;
  
  i64 l = 0, r = 1ll << n;
  
  while (calc(l) + 1 < calc(r)) {
    i64 mid = (l + r) >> 1;
    if (calc(mid) > I) {
      r = mid;
    } else {
      l = mid;
    }
  }

  while (__builtin_popcount(l) > L && calc(l) < I - 1) {
    l++;
  }
  // std::cerr << __builtin_popcount(1) << "\n";

  std::vector<int> ans;
  while (l) {
    ans.push_back(l & 1);
    l >>= 1;
  }
  while (ans.size() < n) {
    ans.push_back(0);
  }
  std::reverse(ans.begin(), ans.end());
  for (auto i : ans) {
    std::cout << i;
  }
  std::cout << "\n";
  
  return 0;
}