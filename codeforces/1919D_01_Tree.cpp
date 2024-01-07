#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

vector<int> a;
struct cmp{
    bool operator()(const int &l,const int &r)const{
        return a[l]<a[r];
    }
};

void solve(){

    int n; cin>>n;
    a=vector<int>(n+5);
    vector<int> L(n+5),R(n+5);
    vector<bool> flag(n+5);
    for(int i=1;i<=n;++i) cin>>a[i];
    priority_queue<int,vector<int>,cmp> pq;
    a[0]=a[n+1]=1e9;
    for(int i=1;i<=n;++i){
        if(i>1&&a[i]==a[i-1]+1||i<n&&a[i]==a[i+1]+1) pq.emplace(i);
        L[i]=R[i]=i;
    }
    if(pq.empty()){
        cout<<"NO"<<endl;
        return;
    }
    int cnt=0;
    function<int(int)> fL=[&](int u){
        if(!L[u]||!flag[L[u]]) return L[u];
        return L[u]=fL(L[u]);
    };
    function<int(int)> fR=[&](int u){
        if(!R[u]||!flag[R[u]]) return R[u];
        return R[u]=fR(R[u]);
    };
    while(pq.size()&&cnt<n-1){
        int u=pq.top();
        pq.pop();
        if(flag[u]) continue;
        flag[u]=1;
        ++cnt;
        L[u]=fL(u-1);
        R[u]=fR(u+1);
        if(L[u]&&R[u]){
            if(a[R[u]]==a[L[u]]+1) pq.emplace(R[u]);
            else if(a[L[u]]==a[R[u]]+1) pq.emplace(L[u]);
        }
    }
    if(cnt<n-1) cout<<"NO"<<endl;
    else{
        for(int i=1;i<=n;++i){
            if(!flag[i]){
                if(a[i]) cout<<"NO"<<endl;
                else cout<<"YES"<<endl;
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
