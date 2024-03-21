#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

ll c[300005];
vector<pii> query[300005];

struct segment{
    ll a[1<<20],lz[1<<20];
    int l0,r0;
    void init(int l,int r){
        l0=l,r0=r;
    }
    void flush(int i,int il,int ir){
        if(il!=ir){
            lz[i<<1]+=lz[i];
            lz[i<<1|1]+=lz[i];
        }
        a[i]+=lz[i]*(ir-il+1);
        lz[i]=0;
    }
    void upd(int i,int il,int ir,int l,int r,ll x){
        if(l>r) return;
        flush(i,il,ir);
        if(l<=il&&ir<=r){
            lz[i]+=x;
            flush(i,il,ir);
            return;
        }
        if(il>r||ir<l) return;
        int im=il+ir>>1;
        upd(i<<1,il,im,l,r,x);
        upd(i<<1|1,im+1,ir,l,r,x);
        a[i]=a[i<<1]+a[i<<1|1];
    }
    void upd(int l,int r,ll x){upd(1,l0,r0,l,r,x);}
    ll qr(int i,int il,int ir,int l,int r){
        flush(i,il,ir);
        if(l<=il&&ir<=r) return a[i];
        if(il>r||ir<l) return 0;
        int im=il+ir>>1;
        return qr(i<<1,il,im,l,r)+qr(i<<1|1,im+1,ir,l,r);
    }
    ll qr(int l,int r){return qr(1,l0,r0,l,r);}
}t;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    ll d; cin>>d;
    for(int i=1;i<=n;++i) cin>>c[i];
    int Q; cin>>Q;
    vector<ll> ans(Q);
    for(int i=0;i<Q;++i){
        int l,r; cin>>l>>r;
        query[r].eb(l,i);
    }
    
    t.init(1,n);
    stack<pair<int,ll>> st;
    st.emplace(0,4e18);
    int L=1;
    for(auto &[l,id]:query[1]) ans[id]=0;
    for(int i=2;i<=n;++i){

        if(c[i]-c[i-1]>=d) st.emplace(i-1,(c[i]-c[i-1])/d);
        else if(c[i]<c[i-1]){
            ll k=(c[i-1]-c[i]+d-1)/d;
            int cur=i-1;
            while(st.top().s<=k){
                t.upd(st.top().f+1,cur,k);
                k-=st.top().s;
                cur=st.top().f;
                st.pop();
            }
            auto [x,y]=st.top();
            st.pop();
            t.upd(x+1,cur,k);
            st.emplace(x,y-k);
        }
        while(t.qr(L,L)*d>c[L]) ++L;

        for(auto &[l,id]:query[i]){
            if(l>=L) ans[id]=t.qr(l,i);
            else ans[id]=-1;
        }
    }
    for(int i=0;i<Q;++i) cout<<ans[i]<<endl;

    return 0;
}
