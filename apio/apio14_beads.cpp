#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second

//#define int ll

const int inf=1e9+7;

vector<pii> adj[200005];
int dp[200005][5];
/**
0: 2
1: 0b
2: 1b
3: 0a
4: 1a
*/

void dfs(int u,int p){
    int mx0=-inf,mx1=-inf,mx2=-inf;
    pii a0={1,-inf},b0={2,-inf},c0={3,-inf};
    int a1=-inf,b1=-inf,c1=-inf;
    int temp,x;
    for(auto &vw:adj[u]){
        if(vw.f!=p){
            dfs(vw.f,u);
            x=max(dp[vw.f][1],vw.s+dp[vw.f][2]);
            dp[u][1]+=x;
            mx0=max(mx0,-x+vw.s+dp[vw.f][1]);
            mx1=max(mx1,-x+max({dp[vw.f][0],dp[vw.f][3],vw.s+dp[vw.f][4]}));
            mx2=max(mx2,-x+vw.s+max({dp[vw.f][0],dp[vw.f][3]}));
            temp=-x+vw.s+dp[vw.f][3];
            if(temp>a0.s) a1=a0.s,a0={vw.f,temp};
            else if(temp>a1) a1=temp;
            temp=-x+vw.s+dp[vw.f][1];
            if(temp>b0.s) b1=b0.s,b0={vw.f,temp};
            else if(temp>b1) b1=temp;
            temp=-x+vw.s+dp[vw.f][0];
            if(temp>c0.s) c1=c0.s,c0={vw.f,temp};
            else if(temp>c1) c1=temp;
        }
    }
    dp[u][2]=dp[u][1]+mx0;
    dp[u][3]=dp[u][1]+mx1;
    dp[u][4]=dp[u][1]+mx2;
    dp[u][0]=dp[u][1]+max({

        b0.s+b1,
        ((a0.f==b0.f)?max(a0.s+b1,a1+b0.s):a0.s+b0.s),
        ((c0.f==b0.f)?max(c0.s+b1,c1+b0.s):c0.s+b0.s)

    });
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=0;i<n-1;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    dfs(1,1);
    cout<<max({dp[1][0],dp[1][1],dp[1][3]});

    return 0;
}
