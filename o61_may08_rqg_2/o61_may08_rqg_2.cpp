#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
#define int ll

const int md=1e9+7;
const int inf=1e9+7;

int pw[]={1,2,4,8,16,32,64,128,256,512,1024,2048};
int X,Y,N;
int id(int x,int y){ return pw[N]*(y-1)+x; }
int mp[1050000];
int idx;
vector<int> adj[350000];

void check(int i,int x,int y){
    if(x<1||y<1||x>pw[N]||y>pw[N]) return;
    if(x==X&&y==Y) return;
    adj[idx].pb(mp[id(x,y)]);
    adj[mp[id(x,y)]].pb(idx);
}

struct A{
    int t,a,b,c;
    bool operator<(const A&o)const{
        if(c==o.c) return b<o.b;
        return c<o.c;
    }
};
vector<A> ans;
int color[1030][1030];

void play(int n,int x,int y,int x0,int y0,int x2,int y2){
    int x1=pw[n-1]+x0-1;
    int y1=pw[n-1]+y0-1;
    if(n==1){
        if(x<=x1&&y<=y1){
            ans.pb({1,0,x0,y0});
        }
        else if(x>x1&&y<=y1){
            ans.pb({2,0,x0,y0});
        }
        else if(x<=x1&&y>y1){
            ans.pb({3,0,x0,y0});
        }
        else{
            ans.pb({4,0,x0,y0});
        }

        return;
    }
    if(x<=x1&&y<=y1){
        ans.pb({1,0,x1,y1});
        play(n-1,x,y,x0,y0,x1,y1);
        play(n-1,x1+1,y1,x1+1,y0,x2,y1);
        play(n-1,x1,y1+1,x0,y1+1,x1,y2);
        play(n-1,x1+1,y1+1,x1+1,y1+1,x2,y2);
    }
    else if(x>x1&&y<=y1){
        ans.pb({2,0,x1,y1});
        play(n-1,x1,y1,x0,y0,x1,y1);
        play(n-1,x,y,x1+1,y0,x2,y1);
        play(n-1,x1,y1+1,x0,y1+1,x1,y2);
        play(n-1,x1+1,y1+1,x1+1,y1+1,x2,y2);
    }
    else if(x<=x1&&y>y1){
        ans.pb({3,0,x1,y1});
        play(n-1,x1,y1,x0,y0,x1,y1);
        play(n-1,x1+1,y1,x1+1,y0,x2,y1);
        play(n-1,x,y,x0,y1+1,x1,y2);
        play(n-1,x1+1,y1+1,x1+1,y1+1,x2,y2);
    }
    else{
        ans.pb({4,0,x1,y1});
        play(n-1,x1,y1,x0,y0,x1,y1);
        play(n-1,x1+1,y1,x1+1,y0,x2,y1);
        play(n-1,x1,y1+1,x0,y1+1,x1,y2);
        play(n-1,x,y,x1+1,y1+1,x2,y2);
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>N>>X>>Y;
    play(N,X,Y,1,1,pw[N],pw[N]);
    sort(ans.begin(),ans.end());
    for(auto &e:ans){
        int x=e.b,y=e.c;
        int c=1;
        if(x-2>=1&&color[x-2][y]==c) ++c;
        if(x-1>=1&&y-1>=1&&color[x-1][y-1]==c) ++c;
        if(y-1>=1&&color[x+1][y-1]==c) ++c;
        if(y-2>=1&&color[x][y-2]==c) ++c;
        color[x][y]=c;
    }
    for(auto &e:ans){
        cout<<e.t<<" "<<color[e.b][e.c]<<" "<<e.b<<" "<<e.c<<endl;
    }


    return 0;
}
/**

4 4 4
6 6 6 6
1
1 1 1


*/
