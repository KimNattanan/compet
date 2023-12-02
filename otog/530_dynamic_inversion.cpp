#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int sq,mxsq,X[200005],Y[200005],Q[100005];
bool flag[200005];
struct fenwick{
    vector<int> bit;
    int n,cnt;
    void init(int n_){
        n=n_;
        bit=vector<int>(n,0);
        cnt=0;
    }
    void add(int i,int x){ ++i;
        for(;i<n;i+=i&-i) bit[i]+=x;
        ++cnt;
    }
    int qr(int i){ ++i;
        int ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw[450];
int st[450],ed[450];
vector<int> idx[450];

ll inv_cnt(vector<int> &vec){
    int n=vec.size();
    if(n<=1) return 0;
    vector<int> L,R;
    for(int i=0;i<(n>>1);++i) L.eb(vec[i]);
    for(int i=(n>>1);i<n;++i) R.eb(vec[i]);
    ll ret=inv_cnt(L)+inv_cnt(R);
    int l=0,r=0;
    vec.clear();
    while(l<L.size()&&r<R.size()){
        if(L[l]>R[r]){
            ret+=L.size()-l;
            vec.eb(R[r++]);
        }
        else vec.eb(L[l++]);
    }
    while(l<L.size()) vec.eb(L[l++]);
    while(r<R.size()) vec.eb(R[r++]);
    return ret;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m;
    while(cin>>n>>m){
        sq=sqrt(n);
        mxsq=(n-1)/sq;
        for(int i=0;i<=mxsq;++i) idx[i].clear();
        for(int i=1;i<=n;++i){
            cin>>Y[i];
            X[Y[i]]=i;
            flag[i]=0;
            idx[(i-1)/sq].eb(Y[i]);
        }
        for(int i=1;i<=m;++i){
            cin>>Q[i];
            flag[X[Q[i]]]=1;
        }
        vector<int> vec;
        for(int i=0;i<=mxsq;++i){
            sort(idx[i].begin(),idx[i].end());
            fw[i].init(idx[i].size()+5);
            st[i]=i*sq+1;
            for(int j=st[i];j-1<(i+1)*sq&&j<=n;++j){
                ed[i]=j;
                if(flag[j]) continue;
                fw[i].add(upper_bound(idx[i].begin(),idx[i].end(),Y[j])-idx[i].begin(),1);
                vec.eb(Y[j]);
            }
        }
        ll cur=inv_cnt(vec);
        stack<ll> ans;
        for(int i=m;i>=1;--i){
            int y=Q[i],x=X[y];
            int block=(x-1)/sq;
            for(int j=0;j<block;++j) cur+=fw[j].cnt-fw[j].qr(upper_bound(idx[j].begin(),idx[j].end(),y)-idx[j].begin());
            for(int j=block+1;j<=mxsq;++j) cur+=fw[j].qr(upper_bound(idx[j].begin(),idx[j].end(),y)-idx[j].begin());
            fw[block].add(upper_bound(idx[block].begin(),idx[block].end(),y)-idx[block].begin(),1);
            for(int j=st[block];j<=ed[block];++j){
                if(j<x&&!flag[j]&&Y[j]>y) ++cur;
                else if(j>x&&!flag[j]&&Y[j]<y) ++cur;
            }
            flag[x]=0;
            ans.emplace(cur);
        }
        while(ans.size()){
            cout<<ans.top()<<endl;
            ans.pop();
        }
    }

    return 0;
}
