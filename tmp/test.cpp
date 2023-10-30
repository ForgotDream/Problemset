int n,p[N];
int ans=0;
signed main(){	
	n=read();
	up(i,1,n-1){
		p[i]=read();
	}
	up(w,1,n){
		memset(dp,0,sizeof dp);
		dp[1][w]=1;
		up(i,2,n){
			up(j,1,n){
				if(j<=n-i+1)dp[i][j]=(dp[i][j]+dp[i-1][j]*ksm((1-p[i-1]+mod)%mod,j))%mod; 
				if(j!=1)dp[i][j-1]=(dp[i][j-1]+dp[i-1][j]*(1-ksm((1-p[i-1]+mod),j-1)+mod)%mod)%mod;
			}
		}
		ans=(ans+w*dp[n][1])%mod;
	}
	cout<<ans;
	return 0;
}

