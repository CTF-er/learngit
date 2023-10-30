#include <bits/stdc++.h>
using namespace std;

int n,m;
struct stuff{
    int u,v,w;
    vector<stuff> a;
};
stuff s[100];
int main(){
    cin >> n >> m;
    int u,v,w;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        s[i].u = u;
        s[i].v = v;
        s[i].w = w;
        if (w!=0){s[w].a.emplace_back(s[i]);}
    }
    vector<int> dp(n+1,0);
    for (int i = 1; i <= m; ++i) {
        if (s[i].w!=0) continue;
        for (int j = n; j >= s[i].u; --j) {
            dp[j] = max(dp[j],dp[j-s[i].u]+s[i].u*s[i].v);
            for (int k = 0; k < s[i].a.size(); ++k) {
                if (j>=s[i].a[k].u+s[i].u){dp[j] = max(dp[j],dp[j-s[i].a[k].u-s[i].u]+s[i].a[k].u*s[i].a[k].v+s[i].u*s[i].v);}
            }
            if (s[i].a.size()==2&&j>=(s[i].u+s[i].a[0].u+s[i].a[1].u)) {
                dp[j] = max(dp[j], dp[j - s[i].u - s[i].a[1].u-s[i].a[0].u] + s[i].u * s[i].v + s[i].a[0].u * s[i].a[0].v +
                                   s[i].a[1].u * s[i].a[1].v);
            }
        }
    }
    cout << dp[n] << endl;
}