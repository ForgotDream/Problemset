#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

ll a, b, c;
ll ans[30][30][30];

ll solve (int a, int b, int c) {
	//cout<<a<<" "<<b<<" "<<c<<endl;
	if(a>0&&a<=20&&b>0&&b<=20&&c>0&&c<=20&&ans[a][b][c]) return ans[a][b][c];
	if(a<=0||b<=0||c<=0) return 1;
	else if(a>20||b>20||c>20) return solve(20, 20, 20);
	else if(a<b&&b<c) return ans[a][b][c] = solve(a, b, c - 1) + solve(a, b - 1, c - 1) - solve(a, b - 1, c);
	else return ans[a][b][c] = solve(a - 1, b, c) + solve(a - 1, b - 1, c) + solve(a - 1, b, c - 1) - solve(a - 1, b - 1, c - 1);
}

int main () {
	while(cin>>a>>b>>c&&(a!=-1||b!=-1||c!=-1)) {
		//memset(ans, 0, sizeof(ans));
		cout<<"w("<<a<<", "<<b<<", "<<c<<") = "<<solve(a, b, c)<<endl;
	}
	return 0;
}
