#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ti3=tuple<int,int,int>;
#define eb emplace_back

bitset<200005> ans;
int a[500005],b[500005],L[500005];
vector<int> vec[500005];

const int N=2000005,N2=4000005;
struct segment1{
    int l0,r0;
    int mn[N2],mx[N2],lz[N2];
    bitset<N2> call;
    segment1(int l0=0,int r0=0):l0(l0),r0(r0){
        for(int i=0;i<N;++i) call[i]=0;
    }
    void flush(int i,int il,int ir){
        if(call[i]){
            if(il<ir){
                lz[2*i]=lz[2*i+1]=lz[i];
                call[2*i]=call[2*i+1]=1;
            }
            mn[i]=mx[i]=lz[i];
            lz[i]=-1;
            call[i]=0;
        }
    }
    void upd(int i,int il,int ir,int l,int r,int val){
        flush(i,il,ir);
        if(l<=il&&ir<=r){
            lz[i]=val;
            call[i]=1;
            flush(i,il,ir);
            return;
        }
        if(il>r||ir<l) return;
        int mid=il+ir>>1;
        upd(2*i,il,mid,l,r,val),upd(2*i+1,mid+1,ir,l,r,val);
        mn[i]=min(mn[2*i],mn[2*i+1]);
        mx[i]=max(mx[2*i],mx[2*i+1]);
    }
    void upd(int l,int r,int val){upd(1,l0,r0,l,r,val);}
    int qr_mn(int i,int il,int ir,int l,int r){
        flush(i,il,ir);
        if(l<=il&&ir<=r) return mn[i];
        if(il>r||ir<l) return 1e9;
        int mid=il+ir>>1;
        return min(qr_mn(2*i,il,mid,l,r),qr_mn(2*i+1,mid+1,ir,l,r));
    }
    int qr_mn(int l,int r){return qr_mn(1,l0,r0,l,r);}
    int qr_mx(int i,int il,int ir,int l,int r){
        flush(i,il,ir);
        if(l<=il&&ir<=r) return mx[i];
        if(il>r||ir<l) return -1;
        int mid=il+ir>>1;
        return max(qr_mx(2*i,il,mid,l,r),qr_mx(2*i+1,mid+1,ir,l,r));
    }
    int qr_mx(int l,int r){return qr_mx(1,l0,r0,l,r);}
}t;

struct segment2{
    int l0,r0;
    int mn[N];
    segment2(int l0=0,int r0=0):l0(l0),r0(r0){}
    void build(int i,int il,int ir){
        if(il==ir) return void(mn[i]=L[il]);
        int mid=il+ir>>1;
        build(2*i,il,mid),build(2*i+1,mid+1,ir);
        mn[i]=min(mn[2*i],mn[2*i+1]);
    }
    void build(){build(1,l0,r0);}
    void upd(int i,int il,int ir,int x,int val){
        if(il==ir) return void(mn[i]=val);
        int mid=il+ir>>1;
        if(x<=mid) upd(2*i,il,mid,x,val);
        else upd(2*i+1,mid+1,ir,x,val);
        mn[i]=min(mn[2*i],mn[2*i+1]);
    }
    void upd(int x,int val){upd(1,l0,r0,x,val);}
    int qr(int i,int il,int ir,int l,int r){
        if(l<=il&&ir<=r) return mn[i];
        if(il>r||ir<l) return 1e9;
        int mid=il+ir>>1;
        return min(qr(2*i,il,mid,l,r),qr(2*i+1,mid+1,ir,l,r));
    }
    int qr(int l,int r){return qr(1,l0,r0,l,r);}
}t2;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i) cin>>b[i];
    int Q; cin>>Q;
    vector<t3> query;
    for(int i=0;i<Q;++i){
        int l,r; cin>>l>>r;
        query.eb(r,l,i);
    }
    sort(query.begin(),query.end());

    t=segment1(1,n<<1);
    t.upd(1,n<<1,0);
    for(int i=1;i<=n;++i){
        L[i]=t.qr_mx(b[i],a[i]);
        t.upd(b[i],a[i],i);
    }
    t.upd(1,n<<1,n+1);
    for(int i=n;i>=1;--i){
        vec[t.qr_mn(b[i],a[i])].eb(i);
        t.upd(b[i],a[i],i);
    }
    t2=segment2(1,n);
    t2.build();
    int now=1;
    for(auto &[r,l,id]:query){
        for(;now<=r;++now){
            for(auto &e:vec[now]) t2.upd(e,n+1);
        }
        ans[id]=t2.qr(l,r)>=l;
    }

    for(int i=0;i<Q;++i) cout<<(ans[i]?"Yes":"No")<<endl;

}
