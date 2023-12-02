#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int P[100005],sz[100005];
using E=tuple<ll,int,int,int>;
vector<E> edge;
using A=tuple<ll,int,int>;
A item[300005];
int fSet(int u){return P[u]=(P[u]==u?u:fSet(P[u]));}
bool uSet(int u,int v){
    int U=fSet(u),V=fSet(v);
    if(U==V) return 0;
    if(sz[U]>sz[V]) swap(U,V);
    P[U]=V;
    sz[V]+=sz[U];
    return 1;
}
bool ans1[200005];
int ans2[300005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,k; cin>>n>>m>>k;
    for(int i=1;i<=m;++i){
        int u,v; cin>>u>>v;
        ll w; cin>>w;
        edge.eb(w,u,v,i);
    }
    for(int i=1;i<=k;++i){
        int u; cin>>u;
        ll w; cin>>w;
        item[i]=A(w,u,i);
    }
    sort(edge.begin(),edge.end());
    sort(item+1,item+1+k);
    for(int i=1;i<=n;++i) P[i]=i,sz[i]=1;
    ll ans0=0;
    vector<int> ans1;
    vector<pii> ans2;
    int cnt=n;
    for(auto &e:edge){
        auto &[w,u,v,i]=e;
        if(cnt-1<=k&&w>get<0>(item[cnt-1])) break;
        if(!uSet(u,v)) continue;
        ans0+=w;
        ans1.eb(i);
        if(--cnt==1) break;
    }
    set<int> ss;
    for(int i=1;i<=n;++i) ss.insert(fSet(i));
    for(int i=1;i<cnt;++i){
        auto &[w,u,j]=item[i];
        ans0+=w;
        u=fSet(u);
        for(auto &e:ss){
            if(e!=u){
                ans2.eb(j,e);
                uSet(u,e);
                if(sz[u]>sz[e]) ss.erase(e);
                else ss.erase(u);
                break;
            }
        }
    }
    cout<<ans0<<endl<<ans1.size()<<endl;
    for(auto &e:ans1) cout<<e<<endl;
    cout<<ans2.size()<<endl;
    for(auto &e:ans2) cout<<e.f<<" "<<e.s<<endl;
    
    return 0;
}
