#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

struct segment{
    vector<segment> child;
    int l,r,mid,mn,lazy;
    segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)),mn(1e9),lazy(0){}
    void flush(){
        if(l!=r&&child.empty()){
            child.eb(l,mid),child.eb(mid+1,r);
            child[0].mn=child[1].mn=mn;
        }
        if(lazy){
            if(l!=r){
                child[0].lazy+=lazy;
                child[1].lazy+=lazy;
            }
            mn+=lazy;
            lazy=0;
        }
    }
    void upd(int i,int x){
        flush();
        if(l==r) return void(mn=x);
        if(i<=mid) child[0].upd(i,x);
        else child[1].upd(i,x);
        mn=min(child[0].mn,child[1].mn);
    }
    void add(int l0,int r0,int x){
        flush();
        if(l0<=l&&r<=r0){
            lazy=x;
            flush();
            return;
        }
        if(l>r0||r<l0) return;
        child[0].add(l0,r0,x),child[1].add(l0,r0,x);
        mn=min(child[0].mn,child[1].mn);
    }
    int qr(int l0,int r0){
        flush();
        if(l0<=l&&r<=r0) return mn;
        if(l>r0||r<l0) return 1e9;
        return min(child[0].qr(l0,r0),child[1].qr(l0,r0));
    }
}t;

void solve(){

    int n; cin>>n;
    vector<int> a(n+5);
    for(int i=1;i<=n;++i) cin>>a[i];
    if(n<3){
        cout<<0<<endl;
        return;
    }
    // vector<vector<int>> dp(n+5,vector<int>(n+5,1e9));
    // dp[1][n+1]=0;
    t=segment(1,n+1);
    t.upd(n+1,0);
    for(int i=2;i<=n;++i){
        int mn1=((a[i]>1)?t.qr(1,a[i]-1):1e9);
        int mn2=t.qr(a[i],n+1);
        if(a[i-1]<a[i]) t.add(1,n+1,1);
        int x=t.qr(a[i-1],a[i-1]);
        t.upd(a[i-1],min({x,mn1+1,mn2}));
        // for(int j=1;j<=n+1;++j) dp[i][j]=dp[i-1][j]+(a[i-1]<a[i]);
        // for(int j=1;j<a[i];++j) dp[i][a[i-1]]=min(dp[i][a[i-1]],dp[i-1][j]+1);
        // for(int j=a[i];j<=n+1;++j) dp[i][a[i-1]]=min(dp[i][a[i-1]],dp[i-1][j]);
    }
    int ans=t.qr(1,n+1);
    // for(int i=1;i<=n+1;++i) ans=min(ans,dp[n][i]);
    cout<<ans<<endl;
    
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }

    return 0;
}
