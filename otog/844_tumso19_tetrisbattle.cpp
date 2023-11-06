#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define endl '\n'
#define pb push_back

int a[100005];
struct info{
    ll pref[3],suf[3],ans[3],sum;
    info(){
        ans[0]=ans[1]=ans[2]=pref[0]=pref[1]=pref[2]=suf[0]=suf[1]=suf[2]=sum=0;
    }
    info operator+(const info &o)const{
        info res;
        int x=sum%3,y=o.sum%3;
        for(int i=0;i<3;++i){
            res.pref[i]=pref[i]+o.pref[(i+3-x)%3];
            res.suf[i]=o.suf[i]+suf[(i+3-y)%3];
            res.ans[i]+=ans[i]+o.ans[i];
            for(int j=0;j<3;++j){
                res.ans[(i+j)%3]+=suf[i]*o.pref[j];
            }
        }
        return res.sum=sum+o.sum,res;
    }
};
struct segment{
    vector<segment> child;
    int l,r,mid;
    info val;
    segment(int l_=0,int r_=0){
        l=l_,r=r_,mid=l+(r-l>>1);
    }
    void build(){
        if(l==r){
            val=info();
            val.ans[a[l]%3]=val.pref[a[l]%3]=val.suf[a[l]%3]=1;
            val.sum=a[l];
            return;
        }
        child.emplace_back(l,mid);
        child.emplace_back(mid+1,r);
        child[0].build(),child[1].build();
        val=child[0].val+child[1].val;
    }
    void upd(int i){
        if(l==r){
            val=info();
            val.ans[a[l]%3]=val.pref[a[l]%3]=val.suf[a[l]%3]=1;
            val.sum=a[l];
            return;
        }
        if(i<=mid) child[0].upd(i);
        else child[1].upd(i);
        val=child[0].val+child[1].val;
    }
    info qr(int l0,int r0){
        if(l0<=l&&r<=r0) return val;
        if(l>r0||r<l0) return info();
        return child[0].qr(l0,r0)+child[1].qr(l0,r0);
    }
}t;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    string s; cin>>s;
    for(int i=0;i<n;++i) a[i]=s[i]-'0';
    t=segment(0,n-1);
    t.build();
    while(Q--){
        int opr,x,y; cin>>opr>>x>>y;
        if(opr==1){
            --x;
            a[x]=y;
            t.upd(x);
        }
        else{
            --x,--y;
            cout<<t.qr(x,y).ans[0]<<endl;
        }
    }

    return 0;
}
