#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second

//#define int ll

vector<pii> edge[4];
int p[2][20005];
int fSet(int u,int z){
    if(p[z][u]==u) return u;
    return p[z][u]=fSet(p[z][u],z);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,k; cin>>n>>m>>k;
    for(int i=0;i<m;++i){
        int u,v,z; cin>>u>>v>>z;
        edge[z].pb({u,v});
    }
    for(int i=1;i<=n;++i){
        p[0][i]=p[1][i]=i;
    }
    for(auto &e:edge[1]){
        int U=fSet(e.f,0),V=fSet(e.s,0);
        if(U==V) continue;
        p[0][U]=V;
    }
    int cnt=0;
    for(auto &e:edge[0]){
        int U=fSet(e.f,0),V=fSet(e.s,0);
        if(U==V) continue;
        p[0][U]=V;
        edge[2].pb(e);
        ++cnt;
    }
    if(cnt>k){
        cout<<"no solution";
        return 0;
    }
    for(auto &e:edge[2]){
        p[1][fSet(e.f,1)]=fSet(e.s,1);
    }
    if(cnt<k){
        for(auto &e:edge[0]){
            int U=fSet(e.f,1),V=fSet(e.s,1);
            if(U==V) continue;
            p[1][U]=V;
            edge[2].pb(e);
            if(++cnt==k) break;
        }
        if(cnt<k){
            cout<<"no solution";
            return 0;
        }
    }
    for(auto &e:edge[1]){
        int U=fSet(e.f,1),V=fSet(e.s,1);
        if(U==V) continue;
        p[1][U]=V;
        edge[3].pb(e);
        ++cnt;
    }
    if(cnt!=n-1) cout<<"no solution";
    else{
        for(auto &e:edge[2]) cout<<e.f<<" "<<e.s<<" 0"<<endl;
        for(auto &e:edge[3]) cout<<e.f<<" "<<e.s<<" 1"<<endl;
    }

    return 0;
}
