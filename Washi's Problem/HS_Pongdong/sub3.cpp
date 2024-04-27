/*
	HS_Pongdong_sub_3
*/
#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using pii = pair<int,int>;
int p[100010],cnt[100010];
int fr(int x){
    return x==p[x]?x:p[x]=fr(p[x]);
}
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,x;cin>>n>>m>>x;
    vector<pii> init(n+1),edge(m+1);
    for(int i=1;i<=n;i++)cin>>init[i].f,p[i]=i,cnt[i]=1;
    for(int i=1;i<=n;i++)cin>>init[i].s;cnt[x]=0;
    for(int i=1;i<=n;i++){
        if(init[i].f<init[x].f&&init[i].s>init[x].s)cnt[i]=0;
        else if(init[i].f>init[x].f&&init[i].s<init[x].s)cnt[i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        u=fr(u),v=fr(v);
        if(u==v)continue;
        p[u]=v,cnt[v]+=cnt[u];
    }
    int q;cin>>q;
    cout<<cnt[fr(x)]<<'\n';
    return 0;
}