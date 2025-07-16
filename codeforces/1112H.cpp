#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
using ll=long long;

ll t[100005],dp[100005],qs[100005],c,d;

struct line{
    ll m,c;
    line(ll m_,ll c_):m(m_),c(c_){}
    ll operator()(const ll &x)const{return m*x+c;}
    ll operator()(const line &o)const{return (long double)(c-o.c)/(o.m-m);}
};
struct cv_hull{
    deque<line> dq;
    bool replace(line a,line b,line c){
        if(b.m==c.m) return b.c>=c.c;
        return a(c)<=a(b);
    }
    void add(line a){
        while(dq.size()>1&&replace(dq[dq.size()-2],dq.back(),a)) dq.pop_back();
        dq.eb(a);
    }
    ll qr(ll x){
        while(dq.size()>1&&dq[1](x)<=dq.front()(x)) dq.pop_front();
        return dq.front()(x);
    }
}cv;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    cin>>c>>d;
    vector<int> vec;
    char p0='a',p1;
    for(int i=1;i<=n;++i){
        cin>>t[i]>>p1;
        qs[i]=t[i]+qs[i-1];
        if(p1!=p0) vec.eb(i);
        p0=p1;
    }
    cin>>t[n+1];
    vec.eb(n+1);
    int m=0;
    deque<line> &dq=cv.dq;
    queue<line> temp;
    for(int i=1;i<=n+1;++i){
        if(vec[m+1]==i){
            ++m;
            dq.clear();
            while(temp.size()) cv.add(temp.front()),temp.pop();
        }
        if(m==0) dp[i]=(i-1)*d;
        else dp[i]=min((i-1)*d,cv.qr(t[i])+d*(i-vec[m])+c*(vec[m]*t[i]-qs[vec[m]-1]));
        temp.emplace(-i*c,dp[i]+c*qs[i-1]);
    }
    cout<<dp[n+1];

    return 0;
}
