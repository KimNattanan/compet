#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second
#define eb emplace_back

bool use[100005];

void solve(){

    int n; cin>>n;
    int sx,sy; cin>>sx>>sy;
    int z=(sx+sy)&1;
    vector<int> odd,even;
    for(int i=1;i<=n;++i){
        int x,y; cin>>x>>y;
        if((x+y)&1) odd.eb(i);
        else even.eb(i);
        use[i]=0;
    }
    if(z){
        if(odd.size()>=even.size()){
            cout<<"First"<<endl;
            cout.flush();
            for(int i=1;i<=n;++i){
                if(i&1){
                    while(odd.size()&&use[odd.back()]) odd.pop_back();
                    while(even.size()&&use[even.back()]) even.pop_back();
                    if(even.size()) use[even.back()]=1,cout<<even.back()<<endl;
                    else use[odd.back()]=1,cout<<odd.back()<<endl;
                    cout.flush();
                }
                else{
                    int x; cin>>x;
                    use[x]=1;
                }
            }
        }
        else{
            cout<<"Second"<<endl;
            cout.flush();
            for(int i=0;i<n;++i){
                if(i&1){
                    while(odd.size()&&use[odd.back()]) odd.pop_back();
                    while(even.size()&&use[even.back()]) even.pop_back();
                    if(odd.size()) use[odd.back()]=1,cout<<odd.back()<<endl;
                    else use[even.back()]=1,cout<<even.back()<<endl;
                    cout.flush();
                }
                else{
                    int x; cin>>x;
                    use[x]=1;
                }
            }
        }
    }
    else{
        if(even.size()>=odd.size()){
            cout<<"First"<<endl;
            cout.flush();
            for(int i=1;i<=n;++i){
                if(i&1){
                    while(odd.size()&&use[odd.back()]) odd.pop_back();
                    while(even.size()&&use[even.back()]) even.pop_back();
                    if(odd.size()) use[odd.back()]=1,cout<<odd.back()<<endl;
                    else use[even.back()]=1,cout<<even.back()<<endl;
                    cout.flush();
                }
                else{
                    int x; cin>>x;
                    use[x]=1;
                }
            }
        }
        else{
            cout<<"Second"<<endl;
            cout.flush();
            for(int i=0;i<n;++i){
                if(i&1){
                    while(odd.size()&&use[odd.back()]) odd.pop_back();
                    while(even.size()&&use[even.back()]) even.pop_back();
                    if(even.size()) use[even.back()]=1,cout<<even.back()<<endl;
                    else use[odd.back()]=1,cout<<odd.back()<<endl;
                    cout.flush();
                }
                else{
                    int x; cin>>x;
                    use[x]=1;
                }
            }
        }
    }

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
