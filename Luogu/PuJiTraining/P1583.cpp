#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
int n, k;
int E[11];
struct node
{
    int w,id;
    bool operator>(const node &b) const
    {
        if(this->w != b.w)
            return this->w > b.w;
        return this->id < b.id;
    }
}all[20001];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= 10; ++i)
        scanf("%d", E + i);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &all[i].w),all[i].id = i;
    sort(all+1,all+1+n,greater<node>());
    for (int i = 1; i <= n; ++i)
        all[i].w += E[((i-1) % 10) + 1];
    sort(all+1,all+1+n,greater<node>());
    for(int i = 1;i<=k;++i)
        printf("%d ",all[i].id);
    return 0;
}