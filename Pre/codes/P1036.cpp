#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, ans;
int a[25];
bool used[25];

bool isPrime (int n) {
	if(n<=3) return n>=2;
	if(n%2==0) return false;
	for(int i = 3; i*i<=n; i+=2) {
		if(n%i==0) return false;
	}
	return true;
}

void dfs (int step = 1, int sum = 0) {
	if(step==n+1) {
		if(isPrime(sum)) ans++;
		return;
	}
	for(int i = 1; i<=n; i++) {
		if(!used[i]) {
			used[i] = true;
			dfs(step+1, sum+a[i]);
			used[i] = false;
		}
	}
	return;
}

int main () {
	cin>>n;
	for(int i = 1; i<=n; i++) {
		cin>>a[i];
	}
    sort(a+1, a+n+1);
	dfs();
	cout<<ans<<endl;
    //cout<<isPrime(19)<<endl;
	return 0;
}
