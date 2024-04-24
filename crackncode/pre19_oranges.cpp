/*
    cnc_pre19_oranges
*/
#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define f first
#define s second

using A=pair<pii,pii>;
A a[100005];
int dp[100005];

bool cmp1(const pii &l,const pii &r){
    return 1LL*l.s*r.f < 1LL*r.s*l.f;
}
bool cmp2(const A &l,const A &r){
    if(l.f!=r.f) return cmp1(l.f,r.f);
    return cmp1(l.s,r.s);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i].f.f>>a[i].f.s>>a[i].s.f>>a[i].s.s;
        if(cmp1(a[i].f,a[i].s)) swap(a[i].f,a[i].s);
    }
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;++i){
        int id=lower_bound(a+1,a+i+1,A(a[i].s,pii(1e9,0)),cmp2)-a-1;
        dp[i]=max(dp[i-1],dp[id]+1);
    }
    cout<<n-dp[n];

    return 0;
}
