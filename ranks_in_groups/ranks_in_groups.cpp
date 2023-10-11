#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define ll long long
#define pii pair<int,int>
#define f first
#define s second

//#define int ll

const int md=1e9+7;
const int inf=1e9+7;

int n;
int p[100005],sz[100005];
int ans[100005][320];
int sq;
int fSet(int u){
    if(p[u]==u) return u;
    return p[u]=fSet(p[u]);
}
bool uSet(int u,int v){
    int U=fSet(u),V=fSet(v);
    if(U==V) return 0;
    if(sz[U]<sz[V]) swap(U,V);
    p[V]=U;
    sz[U]+=sz[V];
    for(int i=0;i<=(n-1)/sq;++i){
        ans[U][i]+=ans[V][i];
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int QQ; cin>>QQ;
    while(QQ--){
        int Q; cin>>n>>Q;
        sq=sqrt(n);
        memset(ans,0,sizeof ans);
        for(int i=0;i<n;++i){
            p[i]=i;
            sz[i]=1;
            ++ans[i][i/sq];
        }
        while(Q--){
            int opr; cin>>opr;
            if(opr==1){
                int u,v; cin>>u>>v; --u,--v;
                uSet(u,v);
            }
            else{
                int u; cin>>u; --u;
                int U=fSet(u);
                int temp=0;
                for(int i=(u/sq)+1;i<=(n-1)/sq;++i) temp+=ans[U][i];
                for(int i=u;i<=n-1&&i/sq==u/sq;++i){
                    if(fSet(i)==fSet(u)) ++temp;
                }
                cout<<temp<<endl;
            }
        }
    }

    return 0;
}
/**


*/
