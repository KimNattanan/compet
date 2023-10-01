#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define ll long long

//#define int ll

const ll md=1e9+7;

const int N=500005;
const int M=5005;
string S[3005];
struct A{
    string *s;
    short int i;
    int adj[29];
    int cnt;
    A(){
        i=-1;
    }
}tree[N];
int temp=0;

ll f[M]={1};

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    for(int i=1;i<M;++i){
        f[i]=(f[i-1]*i)%md;
    }
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        string s; cin>>s;
        S[i]=s;
        int now=0;
        for(int j=0;j<s.length();++j){
            int c=s[j]-'A';
            if(tree[now].adj[c]){
                now=tree[now].adj[c];
                if(tree[now].i!=-1){
                    if(tree[now].i!=tree[now].s->length()-1){
                        tree[now].adj[(*tree[now].s)[tree[now].i+1]-'A']=++temp;
                        if(temp>=N) while(1);
                        ++tree[now].cnt;
                        tree[temp].s=tree[now].s;
                        tree[temp].i=tree[now].i+1;
                        tree[now].i=-1;
                        tree[now].s=NULL;
                    }
                    else{
                        ++tree[now].cnt;
                        tree[now].i=-1;
                    }
                }
            }
            else{
                tree[now].adj[c]=++temp;
                if(temp>=N) while(1);
                ++tree[now].cnt;
                now=temp;
                tree[now].s=&S[i];
                tree[now].i=j;
                goto m1;
            }
        }
        ++tree[now].cnt;
        m1:;
    }
    ll ans=1;
    for(int i=0;i<=temp;++i){
        ans=(ans*f[tree[i].cnt])%md;
    }
    cout<<ans;

    return 0;
}
/**

6
PEAL PEA PEATYAF PEATU PEATR PEA
=144

6
PEAL PEAN PEATY PEATU PEATR PEAK

3
PEATT
PEATTY
HANDSOME
=4

*/
