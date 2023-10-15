
#include<bits/stdc++.h>
using namespace std;
#include "guard.h"
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define f first
#define s second

const ll md=1e9+7;

int pp[168]={
    2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};
map<int,ll> mp[100005];
vector<int> adj[100005];

ll Pow(ll a,ll b){
    ll ans=1;
    while(b>0){
        if(b%2==1) ans=(ans*a)%md;
        a=(a*a)%md;
        b>>=1;
    }
    return ans;
}

std::vector<int> guard(int N, std::vector<int> A, std::vector<int> P) {
    std::vector<int> Ans(N);
    // edit this

    for(int i=0;i<N;++i){
        int x=A[i];
        for(int j=0;j<168&&x>1;++j){
            while(x%pp[j]==0){
                x/=pp[j];
                ++mp[i][pp[j]];
            }
        }
        if(x>1) ++mp[i][x];
        if(i!=0) adj[P[i]].pb(i);
    }
    for(int i=N-1;i>=0;--i){
        pii mx={-1,-1};
        for(auto &v:adj[i]){
            mx=max(mx,{mp[v].size(),v});
        }
        if(mx.s!=-1){
            swap(mp[i],mp[mx.s]);
            ll temp=Ans[mx.s];
            map<int,ll> mp2;
            for(auto &v:adj[i]){
                for(auto &e:mp[v]) mp2[e.f]+=e.s;
            }
            for(auto &e:mp2){
                auto itr=mp[i].find(e.f);
                ll cnt=e.s;
                if(itr!=mp[i].end()){
                    temp=(temp*Pow((itr->s)+1,md-2))%md;
                    cnt+=(itr->s);
                    itr->s += e.s;
                }
                else mp[i][e.f]+=e.s;
                temp=(temp*(cnt+1))%md;
            }
            Ans[i]=temp;
        }
        else{
            ll temp=1;
            for(auto &e:mp[i]){
                temp=(temp*(e.s+1))%md;
            }
            Ans[i]=temp;
        }
    }

    return Ans;
}
