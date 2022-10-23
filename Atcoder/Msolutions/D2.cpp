#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define DEBUG
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e6 + 100;
const double eps = 1e-20;
const double INF = 1e10;
int n,id[maxn];
long long a[maxn]; 
double f[maxn], num[maxn];
template <typename T>
inline T _abs(const T &a) { return a > 0 ? a : -a; }
inline long double getx(int x){return num[x];}
inline long double gety(int x){return 1.0 * num[x] * a[x] - f[x];}
inline long double getslope(int i,int j)
{
    if (getx(i) == getx(j)) return INF;
    return (gety(j) - gety(i)) / (getx(j) - getx(i));
}
bool cmpx(const int &a,const int &b)
{
    return getx(a) < getx(b);
}
bool cmpid(const int &a,const int &b){return a < b;}
int q[maxn],qh,qt;
void cdq(int l,int r)
{
    if (l == r) return (void)(f[l] = std::max(f[l], f[l - 1]), num[l] = f[l] / a[l]);
    int mid = l + r >> 1;
    cdq(l, mid);
    std::sort(id + l,id + r + 1,cmpid);
    std::sort(id + l, id + mid + 1, cmpx);
    qh = 1, qt = 0;
    for (int i = l; i <= mid; ++i)
    {
        while (qt > qh && getslope(q[qt - 1], q[qt]) > getslope(q[qt], id[i])) --qt;
        q[++qt] = i;
    }
    for (int i = mid + 1; i <= r; ++i)
    {
        if(qt == qh) 
        {
            f[id[i]] = std::max(f[id[i]], f[q[qt]] + num[q[qt]] * (a[id[i]] - a[q[qt]]));
            continue;
        }
        int l = qh, r = qt, mid, ans = qt;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (getslope(q[mid], q[mid + 1]) >= a[id[i]]) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        f[id[i]] = std::max(f[id[i]], f[q[ans]] + num[q[ans]] * (a[id[i]] - a[q[ans]]));
    }
    cdq(mid + 1, r);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]),id[i] = i;
    f[1] = 1000;
    cdq(1,n);
    printf("%.2f\n",f[n]);
    return 0;
}