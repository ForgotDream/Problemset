#include<bits/stdc++.h>

using namespace std;

#define int long long
#define inf 0x3f3f3f3f

int read(){
    int a=0;int f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
    return a*f;
}

int n,w[500500],ans[500500],vis[500500];
vector<pair<int,int> >vec[50500];
int dis[1205][1205];

signed main(){
    freopen("syrup.in","r",stdin);
    freopen("syrup.out","w",stdout);
    n=read();
    for(int i=0;i<n;i++){
        w[i]=read();
        ans[i]=1;   
    }
    int a,b,c;
    memset(dis,-1,sizeof dis);
    while(cin>>a>>b>>c){
        dis[a][b]=c;
        dis[b][a]=c;
    }
    int maxl;
    for(int i=0;i<n;i++){
        maxl=inf;
        int k;
        for(int j=0;j<n;j++){
            if(vis[j])continue;
            if(w[j]<maxl){
                k=j;
                //cout<<k<<" "<<i<<" "<<maxl<<endl;
                maxl=w[j];
                //cout<<maxl<<endl;
            }
        }
        vis[k]=1;
        for(int j=0;j<n;j++){
            if(vis[j]&&dis[j][k]!=-1){
                if(w[dis[j][k]]==w[j]+w[k]){
                    ans[dis[j][k]]+=ans[k]*ans[j];
                    //ans[dis[k][j]]+=ans[k]*ans[j];
                    //int ll=dis[j][k];
                    //cout<<w[ll]<<" "<<ans[ll]<<endl;
                }
                if(w[dis[j][k]]>w[j]+w[k]){
                    w[dis[j][k]]=w[j]+w[k];
                    w[dis[k][j]]=w[j]+w[k];
                    ans[dis[j][k]]=ans[k]*ans[j];
                    ans[dis[k][j]]=ans[k]*ans[j];
                    //int ll=dis[j][k];
                    //cout<<w[ll]<<" "<<ans[ll]<<endl;
                }
            }
        }
    }
    cout<<w[0]<<" "<<ans[0]<<endl;
    return 0;
}