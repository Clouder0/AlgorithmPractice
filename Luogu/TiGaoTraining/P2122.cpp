#include <cstdio>
#include <cmath>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e5 + 10;
const int maxpartNum = 1000;
int n, m;
int origin[maxn], pos[maxn];
int L[maxpartNum], R[maxpartNum], tag[maxpartNum], sum[maxpartNum];
inline int gcd(const int &x,const int &y)
{
    if(y)
        return gcd(y,x%y);
    return x;
}
struct num
{
    int up,down;
    num(){}
    num(const int &_up,const int &_down) : up(_up),down(_down){}
    inline void ease()
    {
        int g = gcd(up,down);
        up /= g;
        down /= g;
    }
};
inline void add(int l,int r,int k)
{
    int p = pos[l],q = pos[r];
    if(p == q)
    {
        for(int i = l;i <= r;++i)
            origin[i] += k;
        sum[p] += k * (r - l + 1);
    }
    for(int i = l;i<=R[p];++i)
        origin[i] += k;
    sum[p] += k * (R[p] - l + 1);
    for(int i = L[q];i<=r;++i)
        origin[i] += k;
    sum[q] += k * (r - L[q] + 1);
    for(int i = p + 1;i < q;++i)
        sum[i] += k * (R[i] - L[i] + 1),tag[i] += k;
}
inline int askSum(int l,int r)
{
    int p = pos[l],q = pos[r],res = 0;
    if(p == q)
    {
        for(int i = l;i <= r;++i)
            res += origin[i];
        res += (r - l + 1) * tag[p];
        return res;
    }
    for(int i = l;i<=R[p];++i)
        res += origin[i];
    res += (R[p] - l + 1) * tag[p];
    for(int i = L[q];i<=r;++i)
        res += origin[i];
    res += (r - L[q] + 1) * tag[q];
    for(int i = p + 1;i < q;++i)
        res += sum[i];
    return res;
}
inline void buildPart(const int &x)
{
    for (int j = L[x]; j <= R[x]; ++j)
    {
        read(origin[j]);
        sum[x] += origin[j];
        pos[j] = x;
    }
}
inline void build()
{
    int partSize = sqrt(n);
    int partNum = n / partSize;
    for (int i = 1; i <= partNum; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = L[i] + partSize;
        buildPart(i);
    }
    if (R[partNum] < n)
    {
        ++partNum;
        L[partNum] = R[partNum - 1] + 1;
        R[partNum] = n;
        buildPart(partNum);
    }
}
int main()
{
    read(n);
    read(m);
    build();
    return 0;
}