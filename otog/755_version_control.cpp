#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back

struct A{
    struct node{
        char val;
        int prev;
        node(int prev_=-1,char val_=0):prev(prev_),val(val_){}
    };
    vector<node> vec;
    void init(){vec=vector<node>(1);}
    int push(int prev,char val){
        vec.eb(prev,val);
        return vec.size()-1;
    }
    int push(node x){
        vec.eb(x);
        return vec.size()-1;
    }
    void print(int ver){
        if(vec[ver].prev==-1) return;
        print(vec[ver].prev);
        cout<<vec[ver].val;
    }
}q;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int Q; cin>>Q;
    q.init();
    int cur=0;
    while(Q--){
        char opr; cin>>opr;
        if(opr=='T'){
            char c; cin>>c;
            cur=q.push(cur,c);
        }
        else{
            int x; cin>>x;
            cur=q.push(q.vec[cur-x]);
        }
    }
    q.print(cur);

    return 0;
}
