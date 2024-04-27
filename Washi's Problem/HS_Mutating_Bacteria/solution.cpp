#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll=long long;

int init[100005],L[100005],qs[100005];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int q; cin>>q;
    while(q--){

        int n; cin>>n;
        stack<pair<int,int>> st;
        for(int i=1;i<=n;i++){
            cin>>init[i];
            qs[i]=qs[i-1]+init[i],L[i]=i;
            while(st.size()&&st.top().f<=init[i])L[i]=st.top().s,st.pop();
            st.push({init[i],L[i]});
        }
        while(st.size())st.pop();
        ll ans=0;
        for(int i=n;i>=1;i--){
            int R=i;
            while(st.size()&&st.top().f<=init[i])R=st.top().s,st.pop();
            st.push({init[i],R});
            ans=max(ans,1LL*(qs[L[i]-1]+qs[n]-qs[R])*(R-L[i]+1)*init[i]);
        }
        cout<<ans<<'\n';

    }

    return 0;
}