#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int N,T,F,S,Q;
set<pii> pts[100005];
vector<int> adj[100005];
struct A{
    // t: infect time
    int i,h,t;
    A(int i_=0,int h_=0,int t_=0):i(i_),h(h_),t(t_){}
    vector<pii> vec; // (t2,h2)
    void upd(){
        if(vec.empty()) return;
        sort(vec.begin(),vec.end());
        ll sum=0,cnt=0;
        for(int ii=0;ii<vec.size();++ii){
            if(ii==0) sum=vec[ii].s;
            else{
                int l=vec[ii-1].f,r=vec[ii].f;
                while(l<r){
                    int mid=l+(r-l>>1);
                    if(cnt*1LL*(F+mid-vec[ii-1].f)-1LL*sum>=h) r=mid;
                    else l=mid+1;
                }
                if(l<vec[ii].f){
                    t=min(t,l);
                    break;
                }
                sum=sum-cnt*1LL*(vec[ii].f-vec[ii-1].f)+1LL*vec[ii].s;
            }
            if(vec[ii].s>0) ++cnt;
            else --cnt;
        }
    }
    bool operator<(const A&o)const{
        if(t!=o.t) return t<o.t;
        return i<o.i;
    }
}a[100005];
struct cmp{
    bool operator()(const int &l,const int &r)const{
        return a[l]<a[r];
    }
};
multiset<int,cmp> ms;
bool vis[100005];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>N>>T>>F>>S>>Q;
    for(int i=1;i<=N;++i){
        int x,y,h,v; cin>>x>>y>>h>>v;
        pts[x].insert(pii(y,i));
        a[i]=A(i,h,v?0:1e9);
        ms.insert(i);
    }
    for(int i=0;i<=100000;++i){
        if(pts[i].empty()) continue;
        auto itr1=pts[i].begin(),itr0=itr1++;
        if(i>0){
            auto itr2=pts[i-1].lower_bound(pii(itr0->f,0));
            if(itr2!=pts[i-1].end()&&itr2->f==itr0->f) adj[itr2->s].eb(itr0->s),adj[itr0->s].eb(itr2->s);
        }
        for(;itr1!=pts[i].end();++itr0,++itr1){
            if(i>0){
                auto itr2=pts[i-1].lower_bound(pii(itr1->f,0));
                if(itr2!=pts[i-1].end()&&itr2->f==itr1->f) adj[itr2->s].eb(itr1->s),adj[itr1->s].eb(itr2->s);
            }
            if(itr0->f==itr1->f-1) adj[itr0->s].eb(itr1->s),adj[itr1->s].eb(itr0->s);
        }
    }
    int ans0=0,ans1=0;
    while(ms.size()){
        A &u=a[*ms.begin()]; ms.erase(ms.begin());
        if(u.t>T) break;
        vis[u.i]=1;
        int h2=min(u.h,S)-1,t2=u.t+max(0,u.h-S)+1,t3=u.t+max(1,u.h-Q);
        if(t3>T) ++ans0;
        else ++ans1;
        if(t2>=t3) continue;
        for(auto &vi:adj[u.i]){
            if(vis[vi]) continue;
            A &v=a[vi];
            ms.erase(vi);
            v.vec.eb(t2,h2);
            v.vec.eb(t3,-Q);
            v.upd();
            ms.insert(vi);
        }
    }
    cout<<ans0<<endl<<ans1<<endl;

    return 0;
}

/*

Q<h<S

*/
