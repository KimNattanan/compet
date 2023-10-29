#include "numagain.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll md=1e9+7;

ll a[2005],pw[1000005]={1};

int find_ans(std::vector<int>number)
{

    for(auto &e:number) ++a[e];
    for(int i=1;i<1000005;++i) pw[i]=(pw[i-1]<<1)%md;
    ll ans=0;
    for(int i=1;i<=2000;++i){
        ll sumf,sumg,f,g;
        sumf=sumg=f=g=(pw[a[i]]-1+md)%md;
        for(int j=i+1;j<=2000;++j){
            f=(((pw[a[j]]-1+md)%md)*sumf)%md;
            g=(((pw[a[j]]-1+md)%md)*((sumf+sumg)%md))%md;
            sumf=(sumf+f)%md;
            sumg=(sumg+g)%md;
            ans=(ans+((j-i)*g))%md;
        }
    }

    return ans;
}

/*



*/
