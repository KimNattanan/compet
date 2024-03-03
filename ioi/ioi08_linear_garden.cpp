#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,m,qs[1000005],cnt[5],pw[1000005]={1};
string s;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n>>m>>s;
    set<int> Set;
    Set.insert(0);
    cnt[2]=1;
    for(int i=1;i<=n;++i){
        pw[i]=(pw[i-1]<<1)%m;
        qs[i]=qs[i-1]+(s[i-1]=='L'?-1:1);
        if(!cnt[qs[i]+2]++) Set.insert(qs[i]);
    }

    ll ans=1;
    for(int i=n;i>0;--i){
        if(--cnt[qs[i]+2]==0) Set.erase(qs[i]);
        int mn=*Set.rbegin()-2;
        int mx=*Set.begin()+2;
        if(s[i-1]=='L') continue;
        bool a=qs[i]-4>=mn&&qs[i]-2<=mx;
        bool b=qs[i]-3>=mn&&qs[i]-1<=mx;
        bool c=qs[i]-2>=mn&&qs[i]<=mx;
        ans=(ans+(a+c)*pw[n-i>>1])%m;
        if(b){
            ans=(ans+(a+c)*(m-1))%m;
            ans=(ans+pw[n-i+1>>1])%m;
        }
    }
    cout<<ans;

    return 0;
}
/*
qs[i]=qs[i-1]+1;
qs[i]-2>=mx-2
qs[i]>=mx
qs[i-1]+1>=mx
qs[i-1]>=mx-1;


*/
