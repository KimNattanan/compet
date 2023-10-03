#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

const int inf=1e9;

int p[200005],rnk[200005],val[100005],idx;
int fSet(int u){
    if(p[u]==u) return u;
    return fSet(p[u]);
}
void uSet(int u,int v){
    int U=fSet(u),V=fSet(v);
    if(U==V) return;
    ++idx;
    if(rnk[V]>rnk[U]) swap(U,V);
    if(rnk[U]==rnk[V]||rnk[U]==rnk[V]+1){
        p[U]=p[V]=idx;
        rnk[idx]=rnk[U]+1;
    }
    else{
        p[V]=idx;
        p[idx]=U;
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    idx=n;
    for(int i=1;i<=2*n;++i){
        p[i]=i;
        rnk[i]=0;
    }
    while(Q--){
        int opr; cin>>opr;
        if(opr==1){
            int u,v,w; cin>>u>>v>>w;
            uSet(u,v);
            val[idx-n]=w;
        }
        else if(opr==2){
            int u,v,x; cin>>u>>v;
            vector<int> U,V;

            x=u,U.pb(x);
            while(p[x]!=x) x=p[x],U.pb(x);
            x=v,V.pb(x);
            while(p[x]!=x) x=p[x],V.pb(x);
            while(U.back()==V.back()) U.pop_back(),V.pop_back();

            ll ans=0;
            for(auto &e:U)
                if(e>n) ans+=val[e-n];
            for(auto &e:V)
                if(e>n) ans+=val[e-n];

            cout<<ans<<endl;
        }
    }

    return 0;
}
/**

*/
