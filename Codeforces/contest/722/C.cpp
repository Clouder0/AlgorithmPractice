#include <cstdio>
#include <algorithm>

const int maxn = 1e5 + 100;
int n, fa[maxn], b[maxn], inserted[maxn];
long long a[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void unite(int x,int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    a[x] += a[y], a[y] = 0;
    fa[y] = x;
    // printf("merging %d %d, sum %lld\n", x,y, a[x]);
}
long long ans[maxn];    
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= n; ++i) scanf("%d", b + i);
    for(int i = n;i;--i) {
        int now = b[i];
        if(now > 1 && inserted[now-1]) unite(now,now-1);
        if(now < n && inserted[now+1]) unite(now,now+1);
        inserted[now] = 1;
        ans[i] = std::max(ans[i + 1], a[find(now)]);
        // printf("inserting %d, a[%d]=%lld\n", i, now, a[find(now)]);
    }
    for (int i = 2; i <= n; ++i) printf("%lld\n",ans[i]);
    puts("0");
    return 0;
}