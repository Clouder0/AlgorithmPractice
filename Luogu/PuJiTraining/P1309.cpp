#include <cstdio>
#include <algorithm>
using namespace std;
void read(int &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
struct node
{
    int s, w;
} data[200001];
int winner[100001], loser[100001], all[200001];
bool cmp(const int &a, const int &b)
{
    if (data[a].s != data[b].s)
        return data[a].s > data[b].s;
    return a < b;
}
int n, r, q;
int main()
{
    read(n);
    read(r);
    read(q);
    n <<= 1;
    for (int i = 1; i <= n; ++i)
        read(data[i].s), all[i] = i;
    for (int i = 1; i <= n; ++i)
        read(data[i].w);
    sort(all + 1, all + 1 + n, cmp);
    while (r--)
    {
        for (int i = 1; i < n; i += 2)
        {
            if (data[all[i]].w > data[all[i + 1]].w)
                ++data[all[i]].s,winner[(i>>1)+1] = all[i], loser[(i>>1)+1] = all[i + 1];
            else
                ++data[all[i+1]].s,loser[(i>>1)+1] = all[i], winner[(i>>1)+1] = all[i + 1];
        }
        int p1 = 1,p2 = 1,p = 0;
        while(p1<=n>>1&&p2<=n>>1)
        {
            if(cmp(winner[p1],loser[p2]))
                all[++p] = winner[p1++];
            else
                all[++p] = loser[p2++];
        }
        while(p1<=n>>1)
            all[++p] = winner[p1++];
        while(p2<=n>>1)
            all[++p] = loser[p2++];
    }
    printf("%d", all[q]);
    return 0;
}