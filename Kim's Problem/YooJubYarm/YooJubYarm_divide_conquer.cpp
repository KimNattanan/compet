#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

#define int ll

const int md=1e9+7;
const int inf=1e9+7;

pii a[500005];
int dp0[500005],dp1[500005];

// Divide and Conquer Opt.
void play(int l,int r,int optl,int optr){
    if(l>r) return;
    int mid=l+(r-l>>1);
    pair<ll,int> best={LLONG_MIN,-1};
    for(int i=optl;i<=min(mid,optr);++i){
        best=max(best,{dp0[mid]-dp0[i-1]-(mid-i+1)*a[mid].f,i});
    }
    dp1[mid]=best.f;
    int opt=best.s;
    play(l,mid-1,optl,opt);
    play(mid+1,r,opt,optr);
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int X,Y,Z; cin>>X>>Y>>Z;
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        int val; cin>>val;
        int x,y,z; cin>>x>>y>>z;
        int vx,vy,vz; cin>>vx>>vy>>vz;

        int t=(1.0*abs(x-X)/vx)+(1.0*abs(y-Y)/vy)+(1.0*abs(z-Z)/vz); // math
        a[i]={t,val};
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;++i) dp0[i]=dp0[i-1]+a[i].f+a[i].s; // quick sum
    play(1,n,1,n);
    int ans=0;
    for(int i=1;i<=n;++i){
        ans=max(ans,dp1[i]);
    }

    cout<<ans<<endl;

    return 0;
}
/**

55 55 55
5
5 55 5 55 5 5 5
5 55 5 55 5 55 5
5 5 5 55 5 5 5
5 5 5 5 5 5 5
5 555 555 555 555 55 55


*/
