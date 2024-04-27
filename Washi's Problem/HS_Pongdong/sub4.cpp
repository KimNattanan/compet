/*
	HS_Pongdong_sub_4
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
    for(int i=1;i<=n;i++)cin>>init[i].s;
    for(int i=1;i<=m;i++)cin>>edge[i].f>>edge[i].s;
    int q;cin>>q;
    stack<int> opr,ans;
    vector<bool> cut(m+1,false);
    while(q--){
        int pos;cin>>pos,cut[pos]=true;
        opr.push(pos);
    }
    for(int i=1;i<=m;i++){
        if(cut[i])continue;
        int u=fr(edge[i].f),v=fr(edge[i].s);
        if(u==v)continue;
        p[u]=v,cnt[v]+=cnt[u];
    }
    while(opr.size()){
        ans.push(cnt[fr(x)]-1);
        int pos=opr.top();
        opr.pop();
        int u=fr(edge[pos].f),v=fr(edge[pos].s);
        if(u==v)continue;
        p[u]=v,cnt[v]+=cnt[u];
    }
    cout<<cnt[fr(x)]-1<<'\n';
    while(ans.size())cout<<ans.top()<<'\n',ans.pop();
    return 0;
}