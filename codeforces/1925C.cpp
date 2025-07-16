#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

void solve(){

    int n,k,m; cin>>n>>k>>m;
    string s; cin>>s;
    int mask=0,K=(1<<k)-1;
    string ans;
    for(auto &e:s){
        mask|=1<<e-'a';
        if(mask==K){
            mask=0;
            ans+=e;
        }
    }
    if(ans.size()>=n) cout<<"YES"<<endl;
    else{
        for(int i=0;i<k;++i){
            if(!(mask&(1<<i))){
                cout<<"NO"<<endl<<ans;
                for(int j=ans.size();j<n;++j) cout<<char('a'+i);
                cout<<endl;
                return;
            }
        }
    }

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
