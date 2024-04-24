/*
    cnc_pre19_mangoes
*/
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second

int Tr[100005],Tc[100005],w[100005],qs[5005][5005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,R,C; cin>>n>>m>>R>>C;
    for(int i=1;i<=n;++i) cin>>Tr[i]>>Tc[i]>>w[i];
    for(int i=1;i<=m;++i){
        int Sr,Sc; cin>>Sr>>Sc;
        ++qs[Sr][Sc];
    }
    for(int i=1;i<=R;++i){
        for(int j=1;j<=C;++j){
            qs[i][j]+=qs[i-1][j]+qs[i][j-1]-qs[i-1][j-1];
        }
    }
    int l=0,r=max(R,C);
    while(l<r){
        int mid=l+r>>1;
        bool ok=1;
        for(int i=1;i<=n;++i){
            pii p0={Tr[i]-mid-1,Tc[i]-mid-1}, p1={Tr[i]+mid,Tc[i]+mid};
            p0={max(0,p0.f),max(0,p0.s)}, p1={min(R,p1.f),min(C,p1.s)};
            if(qs[p1.f][p1.s]-qs[p1.f][p0.s]-qs[p0.f][p1.s]+qs[p0.f][p0.s] < w[i]){
                ok=0;
                break;
            }
        }
        if(ok) r=mid;
        else l=mid+1;
    }
    cout<<l;

    return 0;
}
