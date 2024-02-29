#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()

const ll inf=LLONG_MAX>>1;

ll d[100005],P[100005],C[100005],qs[100005],qs2[100005];
pair<ll,int> dp1[100005],dp2[100005];

struct line{
    ll m,c;
    int k;
    line(ll m,ll c,int k):m(m),c(c),k(k){}
    ll operator()(const ll &x)const{return m*x+c;}
};
struct cht{
    deque<line> dq;
    bool check(line f1,line f2,line f3){
        ll x1=(f1.c-f2.c)*(f3.m-f2.m), x2=(f2.c-f3.c)*(f2.m-f1.m);
        if(x1!=x2) return x1>x2;
        return f2.k>f3.k;
    }
    void insert(ll m,ll c,int k=0){
        line f(m,c,k);
        while(sz(dq)>1&&check(dq.end()[-2],dq.back(),f)) dq.pop_back();
        dq.eb(f);
    }
    pair<ll,int> qr(ll x){
        while(sz(dq)>1){
            ll y1=dq.front()(x), y2=dq[1](x);
            if(y1<y2||y1==y2&&dq.front().k<dq[1].k) break;
            dq.pop_front();
        }
        return {dq.front()(x),dq.front().k};
    }
    void clear(){dq.clear();}
}cv1,cv2;
void cal(int n,ll pnt){
    cv1.clear(),cv2.clear();
    cv2.insert(0,pnt,1);
    for(int i=1;i<=n;++i){
        {
            auto [val,k]=cv2.qr(d[i]);
            dp1[i]={val+d[i]*qs[i]-qs2[i]+C[i],k};
            cv1.insert(-d[i],d[i]*qs[i]+dp1[i].f-qs2[i],k);
        }{
            auto [val,k]=cv1.qr(qs[i]);
            dp2[i]={val+qs2[i],k};
            cv2.insert(-qs[i],dp2[i].f+qs2[i]+pnt,k+1);
        }
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    for(int i=2;i<=n;++i){
        cin>>d[i];
        d[i]+=d[i-1];
    }
    for(int i=1;i<=n;++i) cin>>P[i];
    for(int i=1;i<=n;++i) cin>>C[i];
    for(int i=1;i<=n;++i){
        qs[i]=P[i]+qs[i-1];
        qs2[i]=P[i]*d[i]+qs2[i-1];
    }
    if(n<=5000){
        vector<vector<ll>> cost(n+5,vector<ll>(n+5)), dp(2,vector<ll>(n+5));
        for(int i=1;i<=n;++i){
            int mid=i;
            for(int j=i+2;j<=n;++j){
                while(mid+1<j&&d[mid+1]-d[i]<d[j]-d[mid+1]) ++mid;
                cost[i][j]=qs2[mid]-qs2[i]-d[i]*(qs[mid]-qs[i]) + d[j]*(qs[j]-qs[mid])-qs2[j]+qs2[mid];
            }
        }
        for(int i=1;i<=n;++i) dp[1][i]=C[i]+d[i]*qs[i]-qs2[i];
        for(int k=2;k<=m;++k){
            for(int i=k,opt=k-1;i<=n;++i){
                dp[k&1][i]=inf;
                for(int j=opt;j<i;++j){
                    ll w=dp[~k&1][j]+C[i]+cost[j][i];
                    if(w<dp[k&1][i]) dp[k&1][i]=w,opt=j;
                }
            }
        }
        ll ans=dp[m&1][n];
        for(int i=m;i<n;++i) ans=min(ans,dp[m&1][i]+qs2[n]-qs2[i]-d[i]*(qs[n]-qs[i]));
        cout<<ans;
        return 0;
    }
    ll l=0,r=1e11;
    while(l<r){
        ll mid=l+r>>1;
        cal(n,mid);
        if(min(dp1[n],dp2[n]).s>m) l=mid+1;
        else r=mid;
    }
    cal(n,l);
    cout<<min(dp1[n].f,dp2[n].f)-l*m;

    return 0;
}
