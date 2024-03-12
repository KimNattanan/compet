#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
 
struct A{
    multiset<ll> L,R;
    ll mn;
    A():mn(0){}
    void insert(ll x){
        if(L.empty()) L.emplace(x), R.emplace(x);
        else if(x<*L.rbegin()){
            mn+=*L.rbegin()-x;
            L.emplace(x), L.emplace(x);
            R.emplace(*L.rbegin()), L.erase(prev(L.end()));
        }
        else if(x>*R.begin()){
            mn+=x-*R.begin();
            R.emplace(x), R.emplace(x);
            L.emplace(*R.begin()), R.erase(R.begin());
        }
        else L.emplace(x), R.emplace(x);
    }
    A& operator+=(A o){
        if(L.size()<o.L.size()) swap(*this,o);
        
        for(auto &e:o.L){
            if(e<*R.begin()) L.emplace(e); 
            else{
                mn+=e-*R.begin();
                R.emplace(e), L.emplace(*R.begin()), R.erase(R.begin());
            }
        }
        for(auto &e:o.R){
            if(e>*L.rbegin()) R.emplace(e); 
            else{
                mn+=*L.rbegin()-e;
                L.emplace(e), R.emplace(*L.rbegin()), L.erase(prev(L.end()));
            }
        }
        mn+=o.mn;
 
        return *this;
    }
    void clear(){L.clear(),R.clear();}
    int sz(){return L.size()+R.size();}
}t[300005];

vector<int> adj[300005];
int p[300005],big[300005];
ll c[300005];
 
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
 
    int n,m; cin>>n>>m;
    for(int i=2;i<=n+m;++i) cin>>p[i]>>c[i], adj[p[i]].emplace_back(i);
    for(int i=n+m;i>n;--i) t[i].insert(0);
    for(int i=n+m;i>=1;--i){
        if(i<=n) swap(t[i],t[big[i]]);
        for(auto &v:adj[i]){
            if(v==big[i]) continue;
            t[i]+=t[v];
            t[v].clear();
        }
        if(i==1) break;
        while(t[i].R.size()>1){
            auto itr=prev(t[i].R.end());
            t[i].R.erase(itr);
        }
        auto itr1=prev(t[i].L.end()), itr2=t[i].R.begin();
        t[i].L.emplace(*itr1+c[i]), t[i].L.erase(itr1);
        t[i].R.emplace(*itr2+c[i]), t[i].R.erase(itr2);
        if(!big[p[i]] || t[big[p[i]]].sz()<t[i].sz()) big[p[i]]=i;
    }
    cout<<t[1].mn;
 
}
