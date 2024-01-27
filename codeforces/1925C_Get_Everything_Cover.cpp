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
    s=" "+s;
    vector<int> rm(30);
    vector<vector<int>> adj(m+5);
    vector<int> V(m+5);
    vector<int> dp(m+5);
    for(int i=1;i<=m;++i){
        int c=s[i]-'a';
        int mn=1e9;
        for(int j=0;j<k;++j){
            if(rm[j]){
                adj[i].eb(rm[j]);
                if(dp[rm[j]]<mn) mn=dp[rm[j]],V[i]=rm[j];
            }
        }
        if(adj[i].size()==k) dp[i]=mn+1;
        else dp[i]=1,V[i]=0;
        rm[c]=i;
    }
    int u=0;
    for(int i=0;i<k;++i){
        if(dp[rm[i]]<n){
            u=rm[i];
            break;
        }
    }
    if(u==0) cout<<"YES"<<endl;
    else{
        cout<<"NO"<<endl;
        string s2;
        s2.push_back(s[u]);
        while(V[u]!=0){
            u=V[u];
            s2.push_back(s[u]);
        }
        int z=0;
        sort(adj[u].begin(),adj[u].end(),[&](const int &l,const int &r){
            return s[l]<s[r];
        });
        for(auto &e:adj[u]){
            if(s[e]-'a'==z) ++z;
            else break;
        }
        s2.push_back('a'+z);
        reverse(s2.begin(),s2.end());
        cout<<s2<<endl;
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
