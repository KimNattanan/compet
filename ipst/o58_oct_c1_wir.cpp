#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define eb emplace_back
#define f first
#define s second

int a[100005],qs[100005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,Q; cin>>n>>Q;
    for(int i=1;i<=n;++i) cin>>a[i];

    vector<int> vec;
    stack<pair<int,int>> st;
    for(int i=1;i<=n;++i){
        while(st.size()&&st.top().f>a[i]) st.pop();
        if(st.empty()) st.emplace(a[i],0);
        else{
            vec.eb(max(a[i]-st.top().f,st.top().s));
            st.emplace(a[i],vec.back());
        }
    }
    sort(vec.begin(),vec.end());

    while(Q--){
        int x; cin>>x;
        cout<<vec.end()-upper_bound(vec.begin(),vec.end(),x)<<endl;
    }

    return 0;
}
