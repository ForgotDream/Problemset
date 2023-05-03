#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = (int)1e5 + 10;

int n, m;
char S[N];
int a[N];

namespace AC_automaton { //root is vertix #1
	const int N = (int)1e5 + 10;
	const ll INF = (ll)-1e16;
	int node, f, r;
	int ch[N][26], to[N][26], fail[N], str[N], q[N];
	ll dp[2][N];

	void chkmax(ll &a, ll b) { a = a > b ? a : b; }

	int newnode() {
		int res = ++node;
		for (int i = 0; i < 26; ++i) ch[res][i] = 0;
		return fail[res] = str[res] = 0, res;
	}

	void in() { node = 0, newnode(); }
	
	void insert(char *s, int len, int val) {
		int now = 1;
		for (int i = 1; i <= len; ++i) {
			if (ch[now][s[i] - 'a']) now = ch[now][s[i] - 'a'];
			else now = ch[now][s[i] - 'a'] = newnode();
		}
		str[now] += val;
	}

	void build() {
		q[f = r = 1] = 1;
		for ( ; f <= r; ) {
			int x = q[f++];
			for (int i = 0; i < 26; ++i)
				if (ch[x][i]) {
					int p = ch[x][i], k = fail[x];
					for ( ; k && !ch[k][i]; k = fail[k]);
					if (k && ch[k][i] != p) fail[p] = ch[k][i]; else fail[p] = 1;
					q[++r] = p;
				}
		}
	}
	
	void prepare() {
		for (int i = 0; i < 26; ++i) if (ch[1][i]) to[1][i] = ch[1][i]; else to[1][i] = 1;
		for (int i = 2; i <= r; ++i) {
			int x = q[i]; str[x] += str[fail[x]];
			for (int j = 0; j < 26; ++j) {
				if (ch[x][j]) to[x][j] = ch[x][j];
				else to[x][j] = to[fail[x]][j];
			}
		}
	}

	void get_dp() {
		int cur = 0;
		for (int i = 2; i <= node; ++i) dp[0][i] = dp[1][i] = INF;
		dp[1][1] = INF;
		for (int i = 1; i <= m; ++i) {
			for (int j = 0; j < 26; ++j) {
				for (int k = 1; k <= node; ++k) chkmax(dp[cur ^ 1][to[k][j]], dp[cur][k] + (ll)str[to[k][j]]);
			for (int k = 1; k <= node; ++k) dp[cur][k] = INF;
			cur ^= 1;
		}
		ll ans = 0;
		for (int i = 1; i <= node; ++i) chkmax(ans, dp[cur][i]);
		cout << ans << endl;
	}
}

void work() {
    using namespace AC_automaton;
	in();
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i)
		scanf("%s", S + 1), insert(S, strlen(S + 1), a[i]);
	//printf("ok");
	build();//printf("ok");
	prepare();//printf("ok");
	get_dp();
}

int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);

	work();
	return 0;
}
