#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second

//#define int ll

const int inf=1e9+7;

int a[]={0,0,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987};
char b[1005][1005];
void play(int n,int i,int j){
    if(n==1){
        b[i][j]='A';
        return;
    }
    if(n%4==0){
        for(int _i=i;_i<i+a[n];++_i)
            for(int _j=j;_j<j+a[n];++_j)
                b[_i][_j]='A'+n-1;
        play(n-1,i,j+a[n]);
    }
    else if(n%4==1){
        for(int _i=i;_i<i+a[n];++_i)
            for(int _j=j;_j<j+a[n];++_j)
                b[_i][_j]='A'+n-1;
        play(n-1,i+a[n],j);
    }
    else if(n%4==2){
        for(int _i=i;_i<i+a[n];++_i)
            for(int _j=j+a[n-1];_j<j+a[n+1];++_j)
                b[_i][_j]='A'+n-1;
        play(n-1,i,j);
    }
    else{
        for(int _i=i+a[n-1];_i<i+a[n+1];++_i)
            for(int _j=j;_j<j+a[n];++_j)
                b[_i][_j]='A'+n-1;
        play(n-1,i,j);
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n; cin>>n;
    play(n,0,0);
    for(int i=0;i<a[n+1];++i) cout<<b[i]<<endl;

    return 0;
}
/**

*/
