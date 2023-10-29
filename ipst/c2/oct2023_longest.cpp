#include "longest.h"
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

const int inf=1e9+7;
const int md=1e9+7;

std::vector<std::pair<int,int>> longest(int N) {

    std::vector<std::pair<int,int>> ans(N);

    ans[0]={0,0};
    ans[1]={0,1};
    if(N==2) return ans;

    int a=0,b=1;
    bool ch;

    if(find(0,1,2)) a=2;
    else b=2;
    ans[2]={a,b};

    for(int x=3;x<N;++x){
        ch=find(a,b,x);
        if(!ch){
            ch=find(x,b,a);
            if(!ch) b=x;
        }
        else{
            ch=find(x,a,b);
            if(!ch) a=x;
        }
        ans[x]={a,b};
    }


    return ans;
}
