#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int dis[10001];
int arr[10001];
int n,m,s,idx=1;
const int N = 1e4+10,M = 1e5+10;
int h[N],e[M],w[M],ne[M];
void add(int a,int b,int c)
{
    e[idx] = b,w[idx] = c,ne[idx] = h[a],h[a] = idx++;
}
int Dijkstra(int x){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,1});
    memset(dis,0x3f3f3f3f,10001*sizeof(int));
    dis[1] = 0;
    while (!pq.empty()){
        auto t = pq.top();
        pq.pop();
        if (t.first>dis[t.second]||arr[t.second]>x){
            continue;
        }
        for (int i = h[t.second]; i!= -1 ; i=ne[i]) {
            int w1 = w[i];int j = e[i];
            if (dis[j]>t.first+w1&&arr[j]<=x){
                dis[j] = t.first+w1;
                pq.push({dis[j],j});
            }
        }
    }
    return dis[n];
}
int main(){
    cin >> n >> m >> s;
    h[0] = -1;ne[0] = -1;
    int a,b,c;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        add(b,a,c);
        add(a,b,c);
    }
    int r = arr[1];
    for (int i = 0; i < n; ++i) {
        if (r<arr[i+1]){
            r = arr[i+1];
        }
    }
    if (Dijkstra(r)>s){
        cout << "AFK" << endl;
        return 0;
    }
    int l = 1,mid,ans;
    while (l<=r){
        mid = (l+r)/2;
        if (Dijkstra(mid)<=s){
            ans = mid;
            r = mid-1;
        } else{
            l = mid+1;
        }
    }
    cout << ans << endl;
    cout << "WWW" << endl;
    cout << "AAA" << endl;
    cout << "BBB" << endl;
}