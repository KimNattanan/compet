/*
	HS_Pongdong_sub_1
*/
#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using pii = pair<int,int>;
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,x;cin>>n>>m>>x;
    vector<pii> init(n+1);
    for(int i=1;i<=n;i++)cin>>init[i].f;
    for(int i=1;i<=n;i++)cin>>init[i].s;
    for(int i=1;i<=m;i++){int u,v;cin>>u>>v;}
    int q;cin>>q,q++;
    while(q--)cout<<0<<'\n';
    return 0;
}