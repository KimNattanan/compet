#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back

int dp[200005],a[200005],dpL[200005],dpR[200005];

struct fenwick{
    vector<int> bit;
    void init(int n){bit=vector<int>(n);}
    void upd(int i,int x){
        for(;i<bit.size();i+=i&-i) bit[i]=max(bit[i],x);
    }
    int qr(int i){
        int ret=0;
        for(;i>0;i-=i&-i) ret=max(ret,bit[i]);
        return ret;
    }
}fw;

int solve(){
    int n,d; cin>>n>>d;
    int cnt=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        int id=lower_bound(dp,dp+cnt,a[i])-dp;
        if(id==cnt) ++cnt;
        dp[id]=a[i];
        dpL[i]=id+1;
    }
    cnt=0;
    for(int i=n;i>=1;--i){
        int id=lower_bound(dp,dp+cnt,-a[i])-dp;
        if(id==cnt) ++cnt;
        dp[id]=-a[i];
        dpR[i]=id+1;
    }

    vector<int> comp;
    for(int i=1;i<=n;++i) comp.eb(a[i]-d);
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());

    fw.init(comp.size()+5);
    int ans=0;
    for(int i=1;i<=n;++i){
        ans=max(ans,dpR[i]+fw.qr(lower_bound(comp.begin(),comp.end(),a[i])-comp.begin()));
        fw.upd(lower_bound(comp.begin(),comp.end(),a[i]-d)-comp.begin()+1,dpL[i]);
    }
    cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--) solve();

    return 0;
}
