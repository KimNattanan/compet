#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;
const int md=1e9+7;

struct A{
    int L,R;
    int l,r,mid;
    int cnt;
    A(int l_=0,int r_=0,int L_=0,int R_=0):l(l_),r(r_),mid(l+(r-l>>1)),L(L_),R(R_),cnt(0){}
}tree[2400005];
int root[100005],id0;

int a[100005];

void build(int now){
    if(tree[now].l==tree[now].r) return;
    tree[now].L=++id0;
    tree[id0]=A(tree[now].l,tree[now].mid);
    tree[now].R=++id0;
    tree[id0]=A(tree[now].mid+1,tree[now].r);
    build(tree[now].L),build(tree[now].R);
}
void upd(int now,int prev,int x){
    tree[now]=tree[prev];
    if(tree[now].l==tree[now].r) return void(++tree[now].cnt);
    if(x<=tree[now].mid){
        tree[now].L=++id0;
        tree[id0]=A(tree[now].l,tree[now].mid);
        upd(id0,tree[prev].L,x);
    }
    else{
        tree[now].R=++id0;
        tree[id0]=A(tree[now].mid+1,tree[now].r);
        upd(id0,tree[prev].R,x);
    }
    tree[now].cnt=tree[tree[now].L].cnt+tree[tree[now].R].cnt;
}
int query(int vr,int vl,int k){
    if(tree[vr].l==tree[vr].r) return tree[vr].l;
    int cnt=tree[tree[vr].L].cnt-tree[tree[vl].L].cnt;
    if(cnt>=k) return query(tree[vr].L,tree[vl].L,k);
    else return query(tree[vr].R,tree[vl].R,k-cnt);
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    vector<int> vec0;
    for(int i=1;i<=n;++i) cin>>a[i],vec0.pb(a[i]);
    sort(vec0.begin(),vec0.end());
    for(int i=1;i<=n;++i) a[i]=lower_bound(vec0.begin(),vec0.end(),a[i])-vec0.begin()+1;
    tree[0]=A(1,vec0.size());
    build(0);
    for(int i=1;i<=n;++i){
        root[i]=++id0;
        upd(root[i],root[i-1],a[i]);
    }
    while(Q--){
        int l,r,k; cin>>l>>r>>k;
        cout<<vec0[query(root[r],root[l-1],k)-1]<<endl;
    }

    return 0;
}
/**



*/
