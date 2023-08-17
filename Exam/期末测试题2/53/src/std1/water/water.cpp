#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 210 ;
const int INFINITE = 0x3F3F3F3F ;

int n , m ;
vector< pair<int,int> > e[N] ;
int d[N][N] ;

void floyd(){
    for (int k = 1 ; k <= n ; k++){
        for (int i = 1 ; i <= n ; i++){
            if (d[i][k]==INFINITE) continue ;
            for (int j = 1 ; j <= n ; j++)
                d[i][j] = min(d[i][j] , d[i][k] + d[k][j]) ;
        }
    }
}

bool legal(int L){
    vector< pair<int , int> > v ;
    for (int i = 1 ; i <= n ; i++){
        for (int j = 0 ; j < e[i].size() ; j++){
            //
            v.clear() ;
            int x = i , y = e[i][j].first , w = e[i][j].second , k  ;
            for (k = 1 ; k <= n ; k++){
                int l = L - d[x][k] ;
                int r = L - d[y][k] ;
                if (l < 0) l = -1 ;
                if (r < 0) r = -1 ;
                if (l >= w || r >= w) continue ;
                if (l + r >= w) continue ;
                if (l == -1 && r == -1) break ;
                v.push_back(make_pair(l+1,w-r-1)) ;
            }

            if (k == n+1){
                if (v.empty()) return true ;
                sort(v.begin() , v.end()) ;
                int LastMax = 0 ;
                for (int t = 0 ; t < v.size() ; t++){
                    if (LastMax<v[t].first) return true ;
                    if (LastMax<v[t].second+1)
                        LastMax=v[t].second+1 ;
                }
            }
        }
    }
    return false ;
}

void solve(){
    int ans , l = 0 , r = INFINITE ;
    while (l<=r){
        int mid = (l+r)>>1 ;
        if (legal(mid)){
            ans=mid ;
            r=mid-1;
        }else
            l=mid+1;
    }
    printf("%.2lf\n",ans/double(2.0));
}


int main(){

    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    scanf("%d%d",&n,&m);
    memset(d,0x3F,sizeof(d)) ;

    for (int i = 1 ; i <= n ; i++) d[i][i] = 0 ;
    for (int i = 0 ; i < m ; i++){
        int u , v , L ;
        scanf("%d%d%d",&u,&v,&L);
        L<<=1;
        e[u].push_back(make_pair(v,L));
        d[u][v] = d[v][u] = min(d[u][v],L) ;
    }
    floyd();
    solve();
    return 0 ;
}
