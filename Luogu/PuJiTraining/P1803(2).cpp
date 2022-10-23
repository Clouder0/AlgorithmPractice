#include <cstdio>
using namespace std;
struct node
{
    int l, r;
} all[1000001];//保存数据的结构体数组
int s[1000001];//排序数组，保存以右端点位置为下标的线段的编号，即   s[all[i].r] = i
int n, last, ans, maxr;//last为上次选择的线段的右端点
//读入优化部分
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
void read(int &r)
{
    static char c; r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
//
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(all[i].l);
        read(all[i].r);
        maxr = maxr < all[i].r ? all[i].r : maxr;//更新最大右端点，即以后枚举的上界
        if (!s[all[i].r] || all[s[all[i].r]].l < all[i].l)//如果桶的当前位置没有线段，直接放入就好了
            s[all[i].r] = i;//否则以左端点为第二关键字进行排序，左端点大的优先级高
    }
    for (int i = 1; i <= maxr; ++i)//枚举桶位置，依次更新答案
        if (s[i] && all[s[i]].l >= last && ++ans)
            last = all[s[i]].r;
    printf("%d", ans);
    return 0;
}