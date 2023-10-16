#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define f first
#define s second
#define ll long long
#define pb push_back

int bit[100005];
int N,C;
ll dp0[100005];
bool flag[100005];
vector<ll> W;
set<int> ss;
int mxR[100005][20];


int findR(int S,ll F)  { return upper_bound(dp0+S+1,dp0+N+2,F+dp0[S])-dp0-1; }
int findL(int S,ll F)  { return lower_bound(dp0+1,dp0+S+1,dp0[S]-F)-dp0;     }
int findR2(int S,ll F) { return min( *ss.upper_bound(S) ,findR(S,F) );       }
int findL2(int S,ll F) { return max( *(--ss.lower_bound(S)) ,findL(S,F) );   }



int playR0(int S,int T){
    int cnt=0,u=S;
    for(int i=19;i>=0;--i){
        if(mxR[u][i]>=T) continue;
        u=mxR[u][i];
        cnt+=(1<<i);
    }
    ++cnt;
    return cnt;
}


int playR(int S,int T){
    int cnt=0,r=*(--ss.upper_bound(T)),l=*ss.lower_bound(S);
    cnt=0;
    if(l>r) return playR0(S,T);
    if(l!=S){
        cnt+=playR0(S,l);
    }
    if(r!=T){
        cnt+=playR0(r,T);
    }
    for(int i=r;i>0;i-=i&-i) cnt+=bit[i];
    for(int i=l;i>0;i-=i&-i) cnt-=bit[i];
    return cnt;
}


void init_trip(int N_, int Q, int C_, std::vector<int> WW){ N=N_,C=C_;
    W.resize(N+5,0);
    for(int i=1;i<=N;++i) W[i]=WW[i-1];
    for(int i=2;i<=N;++i) dp0[i]=dp0[i-1]+W[i-1];
    dp0[N+1]=INT_MAX;
    ss.insert(1),ss.insert(N);


    int l,r; ll sum;
    l=r=1,sum=0;
    while(l<=N){
        while(r<N&&sum+W[r]<=C) sum+=W[r++];
        mxR[l][0]=r;
        sum-=W[l++];
    }


    for(int i=1;i<20;++i){
        for(int j=1;j<=N;++j){
            mxR[j][i]=mxR[mxR[j][i-1]][i-1];
        }
    }


    bit[N]=playR0(1,N);

    return;
}

void toggle(int G){ ++G;
    if(G!=1&&G!=N){
        if(flag[G]==0){
            auto itrL=ss.upper_bound(G),itrR=itrL--;
            ll sum=playR0(*itrL,*itrR);
            for(int i=*itrR;i<=N;i+=i&-i) bit[i]-=sum;
            sum=playR0(*itrL,G);
            for(int i=G;i<=N;i+=i&-i) bit[i]+=sum;
            sum=playR0(G,*itrR);
            for(int i=*itrR;i<=N;i+=i&-i) bit[i]+=sum;
            ss.insert(G);
        }
        else{
            ss.erase(G);
            auto itrL=ss.upper_bound(G),itrR=itrL--;
            ll sum=playR0(*itrL,*itrR);
            for(int i=*itrR;i<=N;i+=i&-i) bit[i]+=sum;
            sum=playR0(*itrL,G);
            for(int i=G;i<=N;i+=i&-i) bit[i]-=sum;
            sum=playR0(G,*itrR);
            for(int i=*itrR;i<=N;i+=i&-i) bit[i]-=sum;
        }
    }
    flag[G]^=1;
}

int trip(int S, int T, int FF){ ++S,++T;
    int cnt=0;
    ll F=FF;

    if(S<T){
        int nxt=findR2(S,F);
        if(nxt==T) return flag[T];
        if(nxt>T) return 0;
        cnt+=playR(nxt,T);
    }
    else{
        int nxt=findL2(S,F);
        if(nxt==T) return flag[T];
        if(nxt<T) return 0;
        cnt+=playR(T,nxt);
    }

    return cnt+flag[T];
}
