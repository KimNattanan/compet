#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define eb emplace_back
#define sz(x) (int)(x).size()

const int N=500001;

struct fenwick{
    vector<int> bit;
    int cnt;
    void init(int n){bit.assign(n,0),cnt=0;}
    void upd(int i,int x){
        for(;i<sz(bit);i+=i&-i) bit[i]+=x;
        cnt+=x;
    }
    int qr(int i){
        int ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
}fw1,fw2;

vector<int> pts[N+5];

long long find_rec(std::vector<std::vector<int> > Point,int P,int Q){
    vector<int> compI,compJ;
    compI.eb(1),compJ.eb(1);
    fw1.init(N+5),fw2.init(N+5);
    for(auto &e:Point){
        ++e[0],++e[1];
        fw2.upd(e[1],1);
        pts[e[0]].eb(e[1]);
        compI.eb(e[0]),compJ.eb(e[1]);
    }
    sort(compI.begin(),compI.end());
    sort(compJ.begin(),compJ.end());
    compI.erase(unique(compI.begin(),compI.end()),compI.end());
    compJ.erase(unique(compJ.begin(),compJ.end()),compJ.end());
    ll ans=0;
    for(auto &i:compI){
        for(auto &j:pts[i]) fw1.upd(j,1),fw2.upd(j,-1);
        int L,R;
        {
            int l=0,r=sz(compJ)-1;
            while(l<r){
                int mid=l+r+1>>1;
                int j=compJ[mid];
                int a=fw1.qr(j), b=fw1.cnt-a;
                int c=fw2.qr(j), d=fw2.cnt-c;
                if(a-d<=Q&&c-b<=P) l=mid;
                else r=mid-1;
            }
            R=l;
        }
        {
            int l=0,r=sz(compJ)-1;
            while(l<r){
                int mid=l+r>>1;
                int j=compJ[mid];
                int a=fw1.qr(j), b=fw1.cnt-a;
                int c=fw2.qr(j), d=fw2.cnt-c;
                if(d-a<=Q&&b-c<=P) r=mid;
                else l=mid+1;
            }
            L=l;
        }
        if(L<=R) ans+=R-L+1;
    }
    return ans;
}
