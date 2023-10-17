#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int sub=opt<int>(1);
    int X,Y,Z;
    X=rnd.next(200000,100000000);
    if(sub==1) Y=0;
    else Y=rnd.next(200000,100000000);
    if(sub==1||sub==2) Z=0;
    else Z=rnd.next(200000,100000000);
    cout<<X<<" "<<Y<<" "<<Z<<endl;
    int d0,d1,d2,d3,x,y,z;
    x=rnd.next(0,X);
    y=rnd.next(0,Y);
    z=rnd.next(0,Z);
    d0=x+y+z;
    d1=(X-x)+y+z;
    d2=x+(Y-y)+z;
    d3=x+y+(Z-z);
    cout<<d0<<" "<<d1<<" "<<d2<<" "<<d3<<endl;
    int n;
    n=rnd.next(1,500000);
    cout<<n<<endl;
    for(int i=1;i<=n;++i){
        int vx,vy,vz;
        vx=rnd.next(1,max(1,x/rnd.next(12,9876 )) );
        vy=rnd.next(1,max(1,y/rnd.next(56,4912 )));
        vz=rnd.next(1,max(1,z/rnd.next(87,14438 )));
        cout<<vx<<" "<<vy<<" "<<vz<<endl;
    }

    return 0;
}
