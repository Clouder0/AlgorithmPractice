#include <cstdio>
#include <map>
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
const int mod = 10000019;// a number you like((
const int fun = 10000223;// yet another number you like((
int n;
int d[maxn],p[maxn];
int hash[mod + 1];
inline int get(int val) // get number by D
{
    int x = val % mod;
    while(hash[x] && d[hash[x]] != val)
        x = (x ^ fun) % mod;
    return hash[x];
}
inline void put(int x) //put x-th into the hashtable
{
    int pos = d[x] % mod;
    while(hash[pos] && hash[pos] != x)
        pos = (pos ^ fun) % mod;
    hash[pos] = x;
}
std::map<int,int> mp;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        read(d[i]);
        read(p[i]);
//      int old = get(d[i]);
//      if(old == 0)
//          put(i);//no conflict
//     else if(p[old] < p[i])
//          p[old] = p[i];
        std::map<int,int>::iterator it = mp.find(d[i]);
        if(it == mp.end())
            mp[d[i]] = i;
        else if(p[it->second] < p[i])
            p[it->second] = p[i];
    }
    long long ans = 0;
    for(int i = 1;i<=n;++i)
    {
        //int x = get(d[i]);
        //ans += p[x];
        //p[x] = 0;
        ans += p[mp[d[i]]];
        p[mp[d[i]]] = 0;
    }
    printf("%lld",ans);
    return 0;
}