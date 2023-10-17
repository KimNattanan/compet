#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

unordered_set<long long> mp;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int mx=opt<int>(1);
    int X=rnd.next(0, 1000000000);
    int Y=rnd.next(0, 1000000000);
    int Z=rnd.next(0, 1000000000);
    cout<<X<<" "<<Y<<" "<<Z<<endl;

    int n;
    if(mx<=5005) n=rnd.next(0,mx);
    else n=rnd.next(100000,mx);
    cout<<n;

    for(int i=1;i<=n;++i){
        int p,x,y,z,vx,vy,vz;

        p=rnd.next(0, 1000000000);
        x=rnd.next(-1000000000, 1000000000);
        y=rnd.next(-1000000000, 1000000000);
        z=rnd.next(-1000000000, 1000000000);

        int t=rnd.next(0,1000000000);
        while(mp.find(t)!=mp.end()) t=(t+1)%1000000001;
        mp.insert(t);

        double t1=rnd.next(1.0*t+0.9);
        double t2=rnd.next((1.0*t+0.9)-t1);
        double t3=(1.0*t+0.9)-t1-t2;

        if(int(t1)==0) vx=1000000000;
        else vx=max(1,int(1.0*abs(x-X)/t1));
        if(int(t2)==0) vy=1000000000;
        else vy=max(1,int(1.0*abs(y-Y)/t2));
        if(int(t3)==0) vz=1000000000;
        else vz=max(1,int(1.0*abs(z-Z)/t3));

        vx=min(vx,1000000000);
        vy=min(vy,1000000000);
        vz=min(vz,1000000000);

        cout<<endl<<p<<" "<<x<<" "<<y<<" "<<z<<" "<<vx<<" "<<vy<<" "<<vz;
    }
    cout<<endl;

    return 0;
}
