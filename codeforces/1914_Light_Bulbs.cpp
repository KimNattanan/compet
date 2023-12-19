#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

const ll md=998244353;

int L[200005],R[200005],a[400005],lm[400005],rm[400005];

struct segment{
    vector<segment> child;
    int l,r,mid,mn,mx;
    segment(int l_=0,int r_=0):l(l_),r(r_),mid(l+(r-l>>1)){}
    void build(){
        if(l==r){
            mn=lm[l];
            mx=rm[l];
            return;
        }
        child.eb(l,mid),child.eb(mid+1,r);
        child[0].build(),child[1].build();
        mn=min(child[0].mn,child[1].mn);
        mx=max(child[0].mx,child[1].mx);
    }
    void upd(int i){
        if(l==r){
            mn=lm[l];
            mx=rm[l];
            return;
        }
        if(i<=mid) child[0].upd(i);
        else child[1].upd(i);
        mn=min(child[0].mn,child[1].mn);
        mx=max(child[0].mx,child[1].mx);
    }
    int qr_mn(int l0,int r0){
        if(l0<=l&&r<=r0) return mn;
        if(l>r0||r<l0) return 1e9;
        return min(child[0].qr_mn(l0,r0),child[1].qr_mn(l0,r0));
    }
    int qr_mx(int l0,int r0){
        if(l0<=l&&r<=r0) return mx;
        if(l>r0||r<l0) return 0;
        return max(child[0].qr_mx(l0,r0),child[1].qr_mx(l0,r0));
    }
}t;

void play(int i){
    while(1){
        int l=t.qr_mn(lm[i],rm[i]),r=t.qr_mx(lm[i],rm[i]);
        if(l==lm[i]&&r==rm[i]) break;
        lm[i]=l,rm[i]=r;
    }
    t.upd(i);
}

void solve(){
    int n; cin>>n;
    for(int i=1;i<=n;++i) L[i]=R[i]=0;
    for(int i=1;i<=(n<<1);++i) lm[i]=rm[i]=0;
    for(int i=1;i<=(n<<1);++i){
        cin>>a[i];
        if(L[a[i]]==0) L[a[i]]=i;
        R[a[i]]=i;
    }
    for(int i=(n<<1);i>=1;--i) lm[i]=L[a[i]],rm[i]=R[a[i]];
    t=segment(1,n<<1);
    t.build();
    for(int i=1;i<=(n<<1);++i) play(i);
    for(int i=(n<<1);i>=1;--i) play(i);
    vector<pii> vec;
    for(int i=1;i<=n;++i){
        vec.eb(lm[L[i]],rm[R[i]]);
    }
    sort(vec.begin(),vec.end(),[&](const pii &l,const pii &r){
        if(l.f!=r.f) return l.f<r.f;
        return l.s>r.s;
    });
    int now=0,cnt=0;;
    ll ans=1;
    for(int i=0;i<vec.size();++i){
        if(vec[i].f<=now) continue;
        now=vec[i].s;
        int j=i;
        while(j<vec.size()&&vec[j]==vec[i]) ++j;
        ans=(ans*2*(j-i))%md;
        i=j-1;
        ++cnt;
    }
    cout<<cnt<<" "<<ans<<endl;
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
