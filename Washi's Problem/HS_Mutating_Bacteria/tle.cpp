#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll=long long;

int init[100005],L[100005];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int q; cin>>q;
    while(q--){

        int n; cin>>n;
        stack<pair<int,int>> st;
        for(int i=1;i<=n;i++){
            cin>>init[i];
            L[i]=i;
            while(st.size()&&st.top().f<=init[i])L[i]=st.top().s,st.pop();
            st.push({init[i],L[i]});
        }
        while(st.size())st.pop();
        ll ans=0;
        for(int i=n;i>=1;i--){
            int R=i;
            while(st.size()&&st.top().f<=init[i])R=st.top().s,st.pop();
            st.push({init[i],R});
            ll cur=0;
            for(int j=1;j<L[i];j++)cur+=1LL*init[j]*(init[i])*(R-L[i]+1);
            for(int j=R+1;j<=n;j++)cur+=1LL*init[j]*(init[i])*(R-L[i]+1);
            ans=max(ans,cur);
        }
        cout<<ans<<'\n';

    }

    return 0;
}