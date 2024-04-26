/*
    HS_CatBattle
*/
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll md=1e9+7;

int a[100005],b[100005];
ll dp[505][100005], qs[505][100005];
vector<int> comp,cat[505];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    for(int i=0;i<m;++i){
        cin>>a[i]>>b[i];
        comp.push_back(b[i]);
    }
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    for(int i=0;i<m;++i){
        b[i]=lower_bound(comp.begin(),comp.end(),b[i])-comp.begin()+1;
        cat[a[i]].push_back(b[i]);
    }

    int k=comp.size();
    for(int i=0;i<=k;++i) dp[0][i]=1;
    for(int i=1;i<=n;++i){
        dp[i][0]=1;
        for(auto &e:cat[i]) dp[i][e]=(dp[i][e]+qs[i-1][e-1])%md;
        for(int j=1;j<=k;++j) qs[i][j]=((dp[i][j]+qs[i-1][j]+qs[i][j-1]-qs[i-1][j-1])%md+md)%md;
    }
    cout<<(qs[n][k]-1+md)%md;

    return 0;
}