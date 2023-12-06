#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back
 
void solve(){
 
    int n; cin>>n;
    vector<pii> vec(n);
    for(auto &e:vec) cin>>e.f>>e.s;
    int l=0,r=1e9;
    while(l<r){
        int mid=l+(r-l>>1);
        int mn=0,mx=0;
        bool ok=1;
        for(auto &[L,R]:vec){
            if(mn>=R){
                mn=max(L,mn-mid);
                mx=R;
                if(mn>R){
                    ok=0;
                    break;
                }
            }
            else if(mx<=L){
                mx=min(R,mx+mid);
                mn=L;
                if(mx<L){
                    ok=0;
                    break;
                }
            }
            else if(L<=mn&&mx<=R){
                mn=max(mn-mid,L);
                mx=min(mx+mid,R);
            }
            else if(mn<L){
                mx=min(mx+mid,R);
                mn=L;
            }
            else{
                mn=max(mn-mid,L);
                mx=R;
            }
        }
        if(ok) r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
 
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
