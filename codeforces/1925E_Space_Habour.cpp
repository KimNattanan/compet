#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

using A=pair<int,ll>;
ll val0[300005];
ll vL;
int n,m,Q;
set<A> s;

struct segment{
    vector<segment> child;
    ll sum;
    queue<pair<bool,ll>> lz;
    segment(){}
    segment(int l,int r){
        if(l==1&&r==1) sum=0;
        else{
            if(l==1) ++l;
            sum=(((1LL*(r-l+1)*((n<<1)-l-r))>>1)*vL);
        }
    }
    void flush(int &l,int &r){
        if(l!=r&&child.empty()) child.eb(l,l+r>>1),child.eb((l+r>>1)+1,r);
        while(lz.size()){
            auto &[opr,x]=lz.front();
            if(l!=r) child[0].lz.push(lz.front()),
                     child[1].lz.push(lz.front());
            if(opr==0){ // add
                sum+=x*(r-l+1);
            }
            else if(x>0){ // multiply
                sum*=x;
            }
            else{ // divide
                sum/=(-x);
            }
            lz.pop();
        }
    }
    void upd1(int l,int r,int &l0,int &r0,ll &x){
        flush(l,r);
        if(l0<=l&&r<=r0){
            lz.push({0,x});
            flush(l,r);
            return;
        }
        if(l>r0||r<l0) return;
        child[0].upd1(l,l+r>>1,l0,r0,x);
        child[1].upd1((l+r>>1)+1,r,l0,r0,x);
        sum=child[0].sum+child[1].sum;
    }
    void upd2(int l,int r,int &l0,int &r0,ll &x,ll &y){
        flush(l,r);
        if(l0<=l&&r<=r0){
            lz.push({1,-y});
            lz.push({1,x});
            flush(l,r);
            return;
        }
        if(l>r0||r<l0) return;
        child[0].upd2(l,l+r>>1,l0,r0,x,y);
        child[1].upd2((l+r>>1)+1,r,l0,r0,x,y);
        sum=child[0].sum+child[1].sum;
    }
    ll qr(int l,int r,int &l0,int &r0){
        flush(l,r);
        if(l0<=l&&r<=r0) return sum;
        if(l>r0||r<l0) return 0;
        return child[0].qr(l,l+r>>1,l0,r0)+child[1].qr((l+r>>1)+1,r,l0,r0);
    }
    
}t;

void update(int &x,ll &v){
    auto L=s.upper_bound(A(x,LLONG_MAX));
    auto R=L; --L;
    ll temp=-(L->s)*((R->f)-x);
    int a=L->f+1;
    t.upd1(1,n,a,x,temp);
    a=x+1;
    int b=R->f;
    temp=L->s;
    t.upd2(1,n,a,b,v,temp);
    s.insert(A(x,v));
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>m>>Q;
    vector<A> vec(m);
    for(auto &[x,v]:vec) cin>>x;
    for(auto &[x,v]:vec){
        cin>>v;
        if(x==1) vL=v,s.insert({x,v});
        else if(x==n) s.insert({x,v});
    }
    t=segment(1,n);
    for(auto &[x,v]:vec){
        if(x>1&&x<n) update(x,v);
    }
    while(Q--){
        int opr; cin>>opr;
        if(opr==1){
            int x; cin>>x;
            ll v; cin>>v;
            update(x,v);
        }
        else{
            int l,r; cin>>l>>r;
            cout<<t.qr(1,n,l,r)<<endl;
        }
    }

    return 0;
}
