#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

#define int ll

const int inf=1e9+7;

int n;

struct A{
    int l,r,mid,cnt;
    bool call;
    int lazy;
    int sum,mx;
    vector<A> adj;
    A(int _l=1,int _r=n,int _sum=0,int _mx=0){
        l=_l,r=_r,mid=l+(r-l>>1),cnt=(r-l+1);
        call=lazy=0;
        sum=_sum,mx=_mx;
    }
    void flush(){
        if(adj.empty()&&l!=r){
            adj.emplace_back(l,mid);
            adj.emplace_back(mid+1,r);
        }
        if(call){

            sum=lazy*cnt;
            mx=max(lazy,sum);
            if(!adj.empty()){
                adj[0].call=adj[1].call=1;
                adj[0].lazy=adj[1].lazy=lazy;
            }

            call=lazy=0;
        }
    }
    int query(int x){
        flush();
        if(l==r){
            if(mx<=x) return l;
            return l-1;
        }
        adj[0].flush();
        if(adj[0].mx>x) return adj[0].query(x);
        return adj[1].query(x-adj[0].sum);
    }
    void upd(int l0,int r0,int x){
        flush();
        if(r<l0||l>r0) return;
        if(l>=l0&&r<=r0){
            call=1;
            lazy=x;
            flush();
            return;
        }
        adj[0].upd(l0,r0,x);
        adj[1].upd(l0,r0,x);
        sum=adj[0].sum+adj[1].sum;
        mx=max(adj[0].mx,adj[0].sum+adj[1].mx);
    }
};

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>n;

    A tree;

    char c;
    while(cin>>c){
        if(c=='E') return 0;
        if(c=='I'){
            int a,b,x; cin>>a>>b>>x;
            tree.upd(a,b,x);
        }
        else{
            int x; cin>>x;
            cout<<tree.query(x)<<endl;
        }
    }

    return 0;
}
/**

4
Q 1
I 1 4 2
Q 3
Q 1
I 2 2 -1
Q 3
E

*/
