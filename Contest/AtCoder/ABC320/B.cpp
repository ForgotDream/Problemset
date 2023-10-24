#include <cstring>
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 505;
char raw[N], s[N];
int cnt = 0, f[N], d[N];
void init() {
	int len = strlen(raw + 1);
	s[0] = '$';
	for (int i = 1; i <= len; i++)
		s[++cnt] = '#', s[++cnt] = raw[i];
	s[++cnt] = '#', s[++cnt] = '|';
	return;
}

int manacher() {
	int r = 0, mid = 0, res = 0;
	for (int i = 1; i <= cnt; i++) {
		d[i] = (i < r) ? std::min(d[(mid << 1) - i], d[mid] + mid - i) : 1;
		while (s[i + d[i]] == s[i - d[i]]) d[i]++;
		res = std::max(res, d[i]);
		if (d[i] + i > r) r = d[i] + i, mid = i;
	}
	return res - 1;
}
void solve() {
  std::cin >> (raw + 1);
  init();
  std::cout << manacher() << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}