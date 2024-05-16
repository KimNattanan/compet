#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll b[200005],c[200005];
ll cal(int n,ll d){
    ll ret=0;
    for(int i=1;i<=n;++i) ret+=abs(b[i]-d)+abs(c[i]+d);
    return ret;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    for(int i=1;i<=n;++i){
        ll x; cin>>x;
        if(i==1) b[i]=0,c[i]=x;
        else{
            ll y=max(b[i-1],x-c[i-1]);
            b[i]=y, c[i]=x-y;
        }
    }
    ll l=-1e18,r=1e18;
    while(l<r){
        ll mid=l+r>>1;
        if(cal(n,mid)<cal(n,mid+1)) r=mid;
        else l=mid+1;
    }
    cout<<cal(n,l);

    return 0;
}
