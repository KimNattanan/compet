#include "numagain.h"
#include<bits/stdc++.h>
using namespace std;
long long num[2005],num2[2005];
long long md=1e9+7;

int Pow(long long a,long long b){
    long long ans=1;
    while(b>0){
        if(b%2==1) ans=(ans*a)%md;
        a=(a*a)%md;
        b>>=1;
    }
    return ans;
}

int find_ans(std::vector<int>number)
{
    memset(num,0,sizeof num);
    for(auto &e:number){
        ++num2[e];
    }
    for(auto &e:number){
        num[e]=(Pow(2,num2[e])-1+md)%md;
    }
    long long ans=0;
    for(int i=1;i<=2000;++i){
        if(num2[i]==0) continue;
        long long x=2,y=1;
        for(int j=i+1;j<=2000;++j){
            if(num2[j]==0) continue;
            ans=( ans+(((((j-i)*num[i])%md*num[j])%md*x)%md+md)%md )%md;
            x=(x+(((x+y)%md)*num[j])%md)%md;
            y=(y+(y*num[j])%md)%md;
        }
    }
    return ans;
}

//int main(){
//    int n; cin>>n;
//    vector<int> vec(n);
//    for(int i=0;i<n;++i) cin>>vec[i];
//    cout<<find_ans(vec);
//}

/**

A B C D

1+b+c+d+bc+bd+cd+bcd
2+3b+3c+3d+4bc+4bd+4cd+5bcd

(D-A)*( 2*nA*nD + 3*nA*nD*nB + 3*nA*nD*nC + 4*nA*nD*nB*nC )
(D-A)*( 2*nA*nD + 3*nA*nD*(nB + nC) + 4*nA*nD*nB*nC )

(D-A)*nA*nD*(2 + 3*(nB + nC) + 4*nB*nC)

A B C D E

(E-A)*nA*nE*( 2+3*(nB+nC+nD)+4*(nB*nC+nB*nD+nC*nD)+5*(nB*nC*nD) )

(E-A)*nA*nE*( 2+3*(nB+nC+nD)+4*(nB*nC+(nB+nC)*nD)+5*(nB*nC*nD) )

(B-A)*nA*nB*( 2                                                                                                      )
(C-A)*nA*nC*( 2+3*(nB)                                                                                               )
(D-A)*nA*nD*( 2+3*(nB+nC)      +4*(nB*nC)                                                                            )
(E-A)*nA*nE*( 2+3*(nB+nC+nD)   +4*(nB*nC+(nB+nC)*nD)              +5*(nB*nC*nD)                                      )
(F-A)*nA*nF*( 2+3*(nB+nC+nD+nE)+4*(nB*nC+(nB+nC)*nD+(nB+nC+nD)*nE)+5*(nB*nC*nD+(nB*nC+(nB+nC)*nD)*nE)+6*(nB*nC*nD*nE))


(E-A)*nA*nE*( 2+3*(nB+nC)      +4*(nB*nC)
            +(3+4*(nB+nC)      +5*(nB*nC) )*nD

              2+3*(nB+nC)      +4*(nB*nC) + ( 1+(nB+nC)+(nB*nC) )

              2+3*(nB+nC+nD)   +4*(nB*nC+(nB+nC)*nD)              +5*(nB*nC*nD))


              ( 1+(nB+nC)+(nB*nC) )
              ( nD+(nB+nC)nD+nB*nC*nD )
              ( 1+(nB+nC+nD)+(nB*nC+(nB+nC)*nD)+(nB*nC*nD) )

              ans=ans+(A[i]-A[l])*A[i]*A[l]*y
              y=y+(y+x)*A[i]
              x=x+x*A[i]


              1+nB+nC+nD +(nB*nC+(nB+nC)*nD) +(nB*nC*nD)


(F-A)*nA*nF*( 2+3*(nB+nC+nD)   +4*(nB*nC+(nB+nC)*nD)              +5*(nB*nC*nD))  // y

            +(3+4*(nB+nC+nD)   +5*(nB*nC+(nB+nC)*nD)              +6*(nB*nC*nD))*nE


            +3*nE+4*nBnE+4nCnE+4*nDnE +5*nBnCnE+nBnDnE+nCnDnE+6*nB*nC*nD*nE

(C-B)*nB*nC*( 2 )
(D-B)*nB*nD*( 2+3*(nC) )




*/
