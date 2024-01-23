#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

const ll md=998244353;
const int sq=1000;
// int sq;

int n,H[100005],lm[100005],rm[100005],mx;
vector<pii> vec;

struct segment{
    vector<segment> child;
    int sum,lz;
    segment():sum(0),lz(0){}
    void flush(int &l,int &r){
        if(l!=r&&child.empty()){
            child=vector<segment>(2);
            child[0].lz=child[1].lz=sum/(r-l+1);
        }
        if(lz){
            if(l!=r){
                child[0].lz+=lz;
                child[1].lz+=lz;
            }
            sum+=lz*(r-l+1);
            lz=0;
        }
    }
    void add(int &l0,int &r0,int l=1,int r=mx){
        flush(l,r);
        if(l0<=l&&r<=r0){
            ++lz;
            flush(l,r);
            return;
        }
        if(l>r0||r<l0) return;
        child[0].add(l0,r0,l,l+r>>1),child[1].add(l0,r0,(l+r>>1)+1,r);
        sum=child[0].sum+child[1].sum;
    }
    int qr(int &l0,int &r0,int l=1,int r=mx){
        flush(l,r);
        if(l0<=l&&r<=r0) return sum;
        if(l>r0||r<l0) return 0;
        return child[0].qr(l0,r0,l,l+r>>1)+child[1].qr(l0,r0,(l+r>>1)+1,r);
    }
}t[320];

ll play(int l,int r,int &mid,int &h){
    if(l>r) return 1;
    if(H[mid]>=h) return (play(l,mid-1,lm[mid],H[mid])*play(mid+1,r,rm[mid],H[mid]))%md;
    ll cnt=0;
    int bl=l/sq;
    int br=r/sq;
    for(int i=bl;i<=br;++i) ++H[mid],cnt+=t[i].qr(H[mid],h),--H[mid];
    for(int i=l-1;i>=1&&i/sq==bl;--i) cnt-=max(0,min(h,vec[i].s)-max(H[mid],vec[i].f-1));
    for(int i=r+1;i<=n&&i/sq==br;++i) cnt-=max(0,min(h,vec[i].s)-max(H[mid],vec[i].f-1));
    return (cnt%md+(play(l,mid-1,lm[mid],H[mid])*play(mid+1,r,rm[mid],H[mid]))%md)%md;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n;
    // sq=sqrt(n);
    for(int i=1;i<=n;++i) cin>>H[i];
    // int mx=0;
    vec=vector<pii>(n+1);
    for(int i=1;i<=n;++i){
        cin>>vec[i].f>>vec[i].s;
        mx=max(mx,vec[i].s);
    }
    for(int i=1;i<=n;++i) t[i/sq].add(vec[i].f,vec[i].s);

    H[0]=1e9;
    stack<int> st;
    st.emplace(0);
    for(int i=1;i<=n;++i){
        while(H[st.top()]<H[i]) st.pop();
        lm[i]=rm[st.top()];
        rm[st.top()]=i;
        st.emplace(i);
    }

    cout<<play(1,n,rm[0],mx);

    return 0;
}
