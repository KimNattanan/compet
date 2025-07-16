#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

vector<int> adj[2][200005];
int cnt[2][2],a[2][200005],b[2][200005],c[4][200005],z[2][600005];
queue<int> q;

void solve(){
    int n,k; cin>>n>>k;
    for(int i=0;i<2;++i){
        cnt[i][0]=cnt[i][1]=0;
        for(int j=1;j<=n;++j) adj[i][j].clear(),b[i][j]=-1;
        for(int j=1;j<=n;++j) cin>>a[i][j], ++cnt[i][a[i][j]];
        int m; cin>>m;
        for(int j=0;j<m;++j){
            int u,v; cin>>u>>v;
            adj[i][u].eb(v);
        }
    }
    if(cnt[0][0]!=cnt[1][1]) return void(cout<<"NO\n");
    if(!cnt[0][0]||!cnt[0][1]) return void(cout<<"YES\n");
    for(int i=0;i<4;++i) for(int j=0;j<k;++j) c[i][j]=0;
    for(int i=0;i<2;++i){
        q.emplace(1);
        b[i][1]=0;
        ++c[i<<1|a[i][1]][0];
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(auto &v:adj[i][u]){
                if(b[i][v]==-1) b[i][v]=(b[i][u]+1)%k, ++c[i<<1|a[i][v]][b[i][v]], q.emplace(v);
            }
        }
    }
    vector<int> vec(3*k);
    for(int i=0;i<2;++i){
        for(int j=0;j<k;++j) vec[j]=c[i][j];
        for(int j=0;j<k;++j) vec[j+k]=c[2|(i^1)][j];
        for(int j=0;j<k;++j) vec[j+2*k]=c[2|(i^1)][j];
        z[i][0]=vec.size();
        for(int j=1,l=0,r=0;j<vec.size();++j){
            if(r>j) z[i][j]=min(z[i][j-l],r-j);
            else z[i][j]=0;
            while(j+z[i][j]<vec.size()&&vec[j+z[i][j]]==vec[z[i][j]]) ++z[i][j];
            if(j+z[i][j]>r) l=j, r=j+z[i][j];
        }
    }
    for(int i=0;i<k;++i){
        if(z[0][k+i]>=k && z[1][k+(i+2)%k]>=k) return void(cout<<"YES\n");
    }
    cout<<"NO\n";
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int Q; cin>>Q;
    while(Q--) solve();
}
