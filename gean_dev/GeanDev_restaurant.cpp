#include "restaurant.h"
 
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back
 
const ll inf=1e9+7;
 
ll dp0[5000005],a[5000005];
int mnL[5000005],mnR[5000005];
ll MN[5000005],MX[5000005];
 
long long restaurant(int N, std::vector<int> &AA) {
    // edit this
    for(int i=1;i<=N;++i){
        a[i]=abs(AA[i-1]);
        dp0[i]=dp0[i-1]+AA[i-1];
    }
    ll ans=LLONG_MIN;
 
    stack<pair<int,ll>> st;
    st.push({0,0});
    for(int i=1;i<=N;++i){
        MN[i]=dp0[i-1];
        while(!st.empty()&&a[st.top().f]>=a[i]){
            MN[i]=min(MN[i],st.top().s);
            st.pop();
        }
        if(!st.empty()) mnL[i]=st.top().f;
        else mnL[i]=0;
        MN[i]=min(MN[i],dp0[mnL[i]]);
        st.push({i,MN[i]});
    }
    while(!st.empty()) st.pop();
    st.push({N+1,dp0[N]});
    for(int i=N;i>=1;--i){
        MX[i]=dp0[i];
        while(!st.empty()&&a[st.top().f]>=a[i]){
            MX[i]=max(MX[i],st.top().s);
            st.pop();
        }
        if(!st.empty()) mnR[i]=st.top().f;
        else mnR[i]=N+1;
        MX[i]=max(MX[i],dp0[mnR[i]-1]);
        ans=max(ans,a[i]*(MX[i]-MN[i]));
        st.push({i,MX[i]});
    }
 
    for(int i=1;i<=N;++i){
        int L=mnL[i]+1,R=mnR[i]-1;
    }
    return ans;
 
    return 0LL;
}
 
