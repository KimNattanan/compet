#include "stdio.h"

int cmp(const void *l,const void *r){
  return *(int*)l - *(int*)r;
}

int a[200005];

int main(){
  int i;
  int n; scanf("%d",&n);
  for(i=0;i<n;++i){
    int x,y; scanf("%d%d",&x,&y);
    a[i]=x*x+y*y;
  }
  qsort(a,n,sizeof(int),cmp);
  int Q; scanf("%d",&Q);
  while(Q--){
    int x,y; scanf("%d%d",&x,&y);
    int r2=x*x+y*y;
    int l=0,r=n;
    while(l<r){
      int mid=l+r>>1;
      if(a[mid]>=r2) r=mid;
      else l=mid+1;
    }
    printf("%d\n",l);
  }
}