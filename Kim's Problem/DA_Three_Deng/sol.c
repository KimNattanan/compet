#include "stdio.h"

int cnt[3];

int main(){
  int Q; scanf("%d",&Q);
  while(Q--){
    int i;
    int n,m; scanf("%d%d",&n,&m);
    cnt[0]=cnt[1]=cnt[2]=0;
    for(i=0;i<n;++i){
      int x; scanf("%d",&x);
      ++cnt[x%3];
    }
    int ans=(n%3==0);
    if(cnt[1]%3==0){
      if(cnt[2]%3==0) ans+=m;
    }
    else if(cnt[1]%3==1){
      if(cnt[2]%3==1) ans+=m+1>>1;
      else if(cnt[2]%3==2) ans+=m>>1;
    }
    else{
      if(cnt[2]%3==1) ans+=m>>1;
      else if(cnt[2]%3==2) ans+=m+1>>1;
    }
    printf("%d\n",ans);
  }
}