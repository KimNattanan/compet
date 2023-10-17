#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

#define int ll

const int md=1e9+7;
const int inf=1e9+7;

int dp[200005],T[200005];
struct A{
    int m,c;
    A(int m=0,int c=0):m(m),c(c){}
    int operator()(int x)const{
        return m*x+c;
    }
};
bool check(A &a,A &b,A &c){
    int xa=(a.c-b.c)*(c.m-a.m);
    int xb=(a.c-c.c)*(b.m-a.m);
    if(xa<xb)
        return 1;
    return 0;
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int X,Y,Z; cin>>X>>Y>>Z;
    int n; cin>>n;
    vector<pii> vec;
    for(int i=1;i<=n;++i){
        int p,x,y,z,vx,vy,vz; cin>>p>>x>>y>>z>>vx>>vy>>vz;
        int t=(1.0*abs(X-x)/vx)+(1.0*abs(Y-y)/vy)+(1.0*abs(Z-z)/vz);
        vec.pb({t,p});
    }
    sort(vec.begin(),vec.end());
    for(int i=1;i<=n;++i){
        T[i]=vec[i-1].f;
        dp[i]=dp[i-1]+T[i]+vec[i-1].s;
    }
    vector<A> vec2;
    vec2.pb({0,0});
    for(int i=1;i<=n;++i){
        A now={i,-dp[i]};
        int sz=vec2.size();
        while(sz>=2&&check(now,vec2[sz-1],vec2[sz-2])){
            --sz;
            vec2.pop_back();
        }
        vec2.push_back(now);
    }
    int idx=0;
    int ans=0;
    for(int i=1;i<=n;++i){
        int x=T[i];
        while(idx<vec2.size()-1&&vec2[idx+1].m<i&&vec2[idx+1](x)>vec2[idx](x)) ++idx;
        ans=max(ans, vec2[idx](x) + dp[i]-i*T[i] );
    }
    cout<<ans;

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

55 55 55
5
5 55 5 55 5 5 5
555 55 5 55 5 55 5
5 5 5 55 5 5 5
5 5 5 5 5 5 5
55 555 555 555 555 55 55





dp[i]-dp[j]-(i-j)*T[i]

dp[i]-i*T[i] +  j*T[i]-dp[j]

y = ans[i] = max( j( @T[i] ) - dp[j] )  ; 0 <= j < i

ans=max( @ans[i] + dp[i]-i*T[i] )

*/
