#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

int a[2000005],b[2000005],ans[2000005],n;
struct fenwick{
    vector<int> bit;
    int n;
    void init(int n_){
        n=n_;
        bit=vector<int>(n,0);
    }
    void upd(int i,int x){
        for(;i<n;i+=i&-i) bit[i]+=x;
    }
    int qr(int l,int r){
        int ans=0;
        for(;r>0;r-=r&-r) ans+=bit[r];
        for(--l;l>0;l-=l&-l) ans-=bit[l];
        return ans;
    }
}fw;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int _; cin>>_;
    while(_--){
        cin>>n;
        fw.init((n<<1)+5);
        for(int i=1;i<=(n<<1);++i) a[i]=b[i]=ans[i]=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            b[a[i]]=i;
            if(a[i]<i) a[i]+=n;
            else a[i+n]=a[i]+n;
        }
        for(int i=n<<1;i>0;--i){
            if(!a[i]) continue;
            ans[i]=a[i]-i-fw.qr(i,a[i]);
            fw.upd(a[i],1);
        }
        for(int i=1;i<=n;++i) cout<<ans[b[i]]<<" ";
        cout<<endl;
    }

    return 0;
}
