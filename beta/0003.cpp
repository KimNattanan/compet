#include<bits/stdc++.h>
using namespace std;
using ll=long long;

template<class T>
struct Matrix{
    int n,m;
    vector<vector<T>> a;
    Matrix(const int &n=0,const int &m=0):n(n),m(m),a(n,vector<T>(m)){}
    Matrix& operator+=(const Matrix &r){
        for(int i=0;i<n;++i) for(int j=0;j<m;++j) a[i][j]+=r.a[i][j];
        return *this;
    }
    friend Matrix operator+(const Matrix &l,const Matrix &r){return Matrix(l)+=r;}
    friend istream& operator>>(istream &is,Matrix &x){
        for(auto &i:x.a) for(auto &j:i) is>>j;
        return is;
    }
    friend ostream& operator<<(ostream &os,const Matrix &x){
        for(auto &i:x.a){
            for(auto &j:i) os<<j<<" ";
            os<<'\n';
        }
        return os;
    }
};

struct _0003{
    int n,m;
    using matrix=Matrix<ll>;
    matrix m1,m2;
    friend istream& operator>>(istream &is,_0003 &x){
        is>>x.n>>x.m;
        x.m1=x.m2=matrix(x.n,x.m);
        cin>>x.m1>>x.m2;
        return is;
    }
    friend ostream& operator<<(ostream &os,const _0003 &x){
        os<<(x.m1+x.m2);
        return os;
    }
}solution;

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>solution;
    cout<<solution;

    return 0;
}
