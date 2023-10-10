//#include "prison.h"
#include<bits/stdc++.h>
using namespace std;
//#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back

//#define int ll

const int md=1e9+7;
const int inf=1e9+7;

vector<vector<int>> ans(61);
int n;

void playB(int ii,int al,int ar,int bl,int br);
void playA(int ii,int al,int ar,int bl,int br){
    if(al==ar&&bl==br) return;
    if(al>ar||bl>br) return;
    ans[ii][0]=0;
    for(int i=al;i<=ar;++i){
        if(i>br) ans[ii][i]=-2;
        else if(i<bl) ans[ii][i]=-1;
    }
    n=max(n,ii+1);
    if(bl==br) return;
    int mid=bl+1+(br-2-bl>>1);
    int temp=ii+1;
    if(ii%2==1) temp+=2;
    for(int i=bl+1;i<=mid;++i) ans[ii][i]=ii+2;
    for(int i=mid+1;i<=br-1;++i) ans[ii][i]=temp;
    ans[ii][bl]=-1;
    ans[ii+2][bl]=-2;
    ans[temp][bl]=-2;
    ans[ii][br]=-2;
    ans[ii+2][br]=-1;
    ans[temp][br]=-1;
    n=max(n,max(ii+2,temp)+1);
    ans[ii+2][0]=ans[temp][0]=1;
    if(bl+1>=br-1) return;
    playB(ii+2,bl+1,mid,bl+1,br-1);
    playB(temp,mid+1,br-1,bl+1,br-1);
}
void playB(int ii,int al,int ar,int bl,int br){
    if(al==ar&&bl==br) return;
    if(al>ar||bl>ar) return;
    ans[ii][0]=1;
    for(int i=bl;i<=br;++i){
        if(i>ar) ans[ii][i]=-1;
        else if(i<al) ans[ii][i]=-2;
    }
    n=max(n,ii+1);
    if(al==ar) return;
    int mid=al+1+(ar-2-al>>1);
    int temp=ii+1;
    if(ii%2==1) temp+=2;
    for(int i=al+1;i<=mid;++i) ans[ii][i]=ii+2;
    for(int i=mid+1;i<=ar-1;++i) ans[ii][i]=temp;
    ans[ii][al]=-2;
    ans[ii+2][al]=-1;
    ans[temp][al]=-1;
    ans[ii][ar]=-1;
    ans[ii+2][ar]=-2;
    ans[temp][ar]=-2;
    n=max(n,max(ii+2,temp)+1);
    ans[ii+2][0]=ans[temp][0]=0;
    if(al+1>=ar-1) return;
    playA(ii+2,al+1,ar-1,al+1,mid);
    playA(temp,al+1,ar-1,mid+1,ar-1);
}

vector<vector<int>> devise_strategy(int N){
    ans.resize(64);
    for(auto &e:ans) e.resize(N+1);
    n=3;
    int mid=2+(N-2>>1);
    for(int i=2;i<=mid;++i) ans[0][i]=1;
    for(int i=mid+1;i<=N-1;++i) ans[0][i]=2;
    ans[0][1]=-1;
    ans[0][N]=-2;
    ans[1][1]=-2;
    ans[1][N]=-1;
    ans[2][1]=-2;
    ans[2][N]=-1;
    ans[1][0]=ans[2][0]=1;
    if(N!=2){
        playB(1,2,mid,2,N-1);
        playB(2,mid+1,N-1,2,N-1);
    }
    cout<<n<<" ====="<<endl;
    ans.resize(n);
    return ans;
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    vector<vector<int>> ans;
    int n; cin>>n;
    ans=devise_strategy(n);
    cout<<"[\n";
    for(int i=0;i<1;++i){
        cout<<"[";
        auto e=ans[(ans.size()-1)-2];
        for(auto &f:e) cout<<f<<" ";
        cout<<"]\n";
    }
    cout<<"]";

    return 0;
}
/**



*/

