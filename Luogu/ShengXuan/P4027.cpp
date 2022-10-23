#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
const double eps = 1e-18,inf = 1e30;
struct node
{
    int pos;
    double x,y;
} Q[maxn],tmp[maxn];
double f[maxn],A[maxn],B[maxn],R[maxn];
int queue[maxn],head,tail;
int n,initMoney;
bool cmp(const node a, const node b) { return -(A[a.pos] / B[a.pos]) > -(A[b.pos] / B[b.pos]); }
double slope(int x,int y)
{
    if(Q[x].x == Q[y].x) return inf;
    return (Q[x].y - Q[y].y) / (Q[x].x - Q[y].x);
}
void cdq(int l,int r)
{
    if(l == r)
    {
        f[l] = max(f[l],f[l-1]);
        Q[l].x = R[l] / (A[l] * R[l] + B[l]) * f[l];
        Q[l].y = f[l] / (A[l] * R[l] + B[l]);
        return;
    }
    int mid = l + r >>1;
    for(int i = l,p = l,q = mid + 1;i<=r;++i)
        if(Q[i].pos <= mid) tmp[p++] = Q[i];
        else tmp[q++] = Q[i];
    for(int i = l;i<=r;++i) Q[i] = tmp[i];
    cdq(l,mid);
    head = 1,tail = 0;
    for(int i = l;i<=mid;++i)
    {
        while(tail > head && slope(queue[tail],i) > slope(queue[tail - 1],queue[tail])) --tail;
        queue[++tail] = i;
    }
    for(int i = mid + 1;i<=r;++i)
    {
        while(tail > head && slope(queue[head],queue[head + 1]) > -A[Q[i].pos] / B[Q[i].pos]) ++head;
        f[Q[i].pos] = max(f[Q[i].pos],Q[queue[head]].x * A[Q[i].pos] + Q[queue[head]].y * B[Q[i].pos]);
    }
    cdq(mid + 1,r);
    int p = l,q = mid + 1,k = l;
    while(p <= mid && q <= r)
        if(Q[p].x < Q[q].x) tmp[k++] = Q[p++];
        else tmp[k++] = Q[q++];
    while(p <= mid) tmp[k++] = Q[p++];
    while(q <= r) tmp[k++] = Q[q++];
    for(int i = l;i<=r;++i) Q[i] = tmp[i];
}
int main()
{
    scanf("%d %d",&n,&initMoney);
    for (int i = 1; i <= n; ++i) scanf("%lf %lf %lf", A + i, B + i, R + i);
    for (int i = 1; i <= n; ++i)
    {
        Q[i].pos = i; 
        f[i] = initMoney;
        Q[i].x = f[i] / (A[i] * R[i] + B[i]) * R[i];
        Q[i].y = f[i] / (A[i] * R[i] + B[i]);
    }
    sort(Q + 1,Q + 1 + n,cmp);
    cdq(1,n);
    printf("%.5f",f[n]);
    return 0;
}