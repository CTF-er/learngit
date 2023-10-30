#include<bits/stdc++.h>
#include <fstream>
using namespace std;

int n,m;
const int N = 1e5+10;
long long arr[N];
long long diff[N];
long long sum[N*4];
long long lazy[N*4];

void Pushup(int rt){
    sum[rt] = sum[rt<<1]+sum[rt<<1|1];
}
void Pushdown(int ln,int rn,int rt){
    if (lazy[rt]!= 0){
        sum[rt<<1] += lazy[rt]*ln;
        lazy[rt<<1] += lazy[rt];
        sum[rt<<1|1] += lazy[rt]*rn;
        lazy[rt<<1|1] += lazy[rt];
        lazy[rt] = 0;
    }
}
void Build(int l,int r,int rt){
    if (l == r){
        sum[rt] = diff[l];
        return;
    }
    int m = (l+r)>>1;
    Build(l,m,rt<<1);
    Build(m+1,r,rt<<1|1);
    Pushup(rt);
}
void add(int L,int R,int l,int r,int rt,int d){
    if (L<=l&&r<=R){
        sum[rt] += (r-l+1)*d;
        lazy[rt] += d;
        return;
    }
    int m = (l+r)>>1;
    Pushdown(m-l+1,r-m,rt);
    if (L<=m){ add(L,R,l,m,rt<<1,d);}
    if (R>m){ add(L,R,m+1,r,rt<<1|1,d);}
    Pushup(rt);
    return;
}
long long Query(int L,int R,int l,int r,int rt){
    if (L<=l&&r<=R){
        return sum[rt];
    }
    int m = (l+r)>>1;
    Pushdown(m-l+1,r-m,rt);
    long long ans = 0;
    if (L<=m){ans += Query(L,R,l,m,rt<<1);}
    if (R>m){ans += Query(L,R,m+1,r,rt<<1|1);}
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    diff[1] = arr[1];
    for (int i = 2; i <= n; ++i) {
        diff[i] = arr[i]-arr[i-1];
    }
    Build(1,n,1);
    int opt;
    int l,r,k,d,p;
    for (int i = 0; i < m; ++i) {
        cin >> opt;
        if (opt==1){
            cin >> l >> r >> k >> d;
            add(l,l,1,n,1,k);
            if (l+1<=r){
                add(l+1,r,1,n,1,d);
            }
            if (r<n){ add(r+1,r+1,1,n,1,-(k+d*(r-l)));}
        } else{
            cin >> p;
            cout << Query(1,p,1,n,1) << endl;
        }
    }
}