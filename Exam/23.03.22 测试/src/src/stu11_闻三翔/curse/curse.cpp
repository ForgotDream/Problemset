# include <cstdio>
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cmath>
using namespace std;
typedef long long i64;
const int N = 2000;
i64 sum[3][N];
char ch[N];
int L, n;
int main()
{
	freopen("curse.in", "r", stdin);
	freopen("curse.out", "w", stdout);
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >>n;
	cin >>(ch + 1);
	L = strlen(ch + 1);
	for(int i = 1; i <= L; i ++) {
		sum[ch[i] - '0'][i] ++;
	} 
	for(int i = 2; i <= n; i ++) {
		cin >>(ch + 1);
		for(int j = 1; j <= L; j ++) {
			sum[ch[j] - '0'][j] ++;
		}
	}
	for(int i = 1; i <= L; i ++) {
		if(sum[0][i] >= sum[1][i]) {
			cout <<"0";
		}
		else cout <<"1";
	}
	return 0;
}

