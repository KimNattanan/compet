#include <bits/stdc++.h>
#define f first
#define s second
#define int long long
using namespace std;
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;cin>>q;
    while(q--){
        int n,ans=0,sum=0;cin>>n;
        vector<int> init(n);
        for(int &x:init)cin>>x,sum+=x;
        for(int i=0;i<n;i++){
            int l=i,r=i;
            int SUM=sum-init[i];
            while(l-1>=0&&init[l-1]<=init[i])SUM-=init[--l];
            while(r+1<n&&init[r+1]<=init[i])SUM-=init[++r];
            ans=max(ans,SUM*(r-l+1)*init[i]);
        }
        cout<<ans<<'\n';
    }
    return 0;
}