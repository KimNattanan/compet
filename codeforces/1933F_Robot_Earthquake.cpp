#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()
 
const int inf=1e9;
 
bitset<1005> a[1005];
int d[1005][1005];
 
void solve(){
    int n,m; cin>>n>>m;
 
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            bool x; cin>>x;
            a[i][j]=x;
            d[i][j]=inf;
        }
    }
 
    queue<pii> q;
    q.emplace(0,0);
    d[0][0]=0;
    int ans=inf;
    while(q.size()){
        auto &[ii,jj]=q.front(); q.pop();
        if(jj==m-1){
            int tmp=((ii-d[ii][jj])%n+n)%n;
            if(tmp!=n-1) ans=min(ans,d[ii][jj]+tmp+1);
            else ans=min(ans,d[ii][jj]);
        }
        if(jj+1<m&&d[(ii+1)%n][jj+1]>d[ii][jj]+1&&!a[(ii+1)%n][jj+1]){
            d[(ii+1)%n][jj+1]=d[ii][jj]+1;
            q.emplace((ii+1)%n,jj+1);
        }
        if(d[(ii+2)%n][jj]>d[ii][jj]+1&&!a[(ii+2)%n][jj]&&!a[(ii+1)%n][jj]){
            d[(ii+2)%n][jj]=d[ii][jj]+1;
            q.emplace((ii+2)%n,jj);
        }
    }
    if(ans==inf) cout<<-1<<endl;
    else cout<<ans<<endl;
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }
}
