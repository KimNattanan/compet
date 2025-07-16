#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
#define sz(x) (int)(x).size()

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    priority_queue<int> pq;
    ll ans=0;
    for(int i=0;i<n;++i){
        int x; cin>>x;
        pq.emplace(x-i),pq.emplace(x-i);
        if(x!=pq.top()+i) ans+=abs(x-pq.top()-i);
        pq.pop();
    }
    cout<<ans;
    
}
