#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

ll a[2000005];
int lm[2000005];

ll play(int l,int r){
    if(l>r) return 0;
    ll ret=0;
    int u=r;
    while(u>=l){
        ret+=a[u]*(u-max(l-1,lm[u]));
        u=lm[u];
    }
    return ret;
}

void solve(){

    int n; cin>>n;
    stack<int> st;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        a[i+n]=a[i];
    }
    st.emplace(0);
    for(int i=1;i<=n+n;++i){
        while(a[st.top()]>a[i]) st.pop();
        lm[i]=st.top();
        st.emplace(i);
    }
    if(n==1){cout<<1<<endl;return;}
    ll now=play(2,n),ans=now;
    for(int i=n+n;i>n;--i){
        now-=a[i]*(i-max(i-n+1,lm[i]));
        now+=play(lm[i]+1,i-1);
        if(a[i]==0&&lm[i]!=i-n) now+=1;
        ans=max(ans,now);
    }

    cout<<ans+n<<endl;

}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q(1);
    cin>>Q;
    while(Q--){
        solve();
    }

    return 0;
}
