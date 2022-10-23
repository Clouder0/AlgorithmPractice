#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;
const int maxn = 2e4 + 10;
map<string,int> mp;
int n,m,k;
int fa[maxn],rnk[maxn];
int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &a,const int &b)
{
    int x = find(a),y = find(b);
    if(x == y)
        return;
    if(rnk[x] == rnk[y])
        fa[x] = y,rnk[x]++;
    else if(rnk[x] > rnk[y])
        fa[y] = x;
    else
        fa[x] = y;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    string s;
    for(int i = 1;i<=n;++i)
    {
        cin >> s;
        mp[s] = i;
        fa[i] = i;
    }
    string a,b;
    for(int i = 1;i<=m;++i)
    {
        cin >> a >> b;
        unite(mp[a],mp[b]);
    }
    cin >> k;
    for(int i = 1;i<=k;++i)
    {
        cin >> a >> b;
        if(find(mp[a]) == find(mp[b]))
            puts("Yes.");
        else
            puts("No.");
    }
    return 0;
}