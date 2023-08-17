#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

int t, n;
map<int, int> mp;

int main () {
	cin>>t;
	while(t--) {
		memset(a, 0, sizeof(a));
		cin>>n;
		int tmp, l = 0, ans = 0;
		for(int i = 1; i<=n; i++) {
			cin>>tmp;
			if(mp[tmp]>l) l = mp[tmp];
			ans = max(ans, i - l);
			mp[tmp] = i;
		}
		cout<<ans<<endl;
		mp.clear();
	}
	return 0;
}
