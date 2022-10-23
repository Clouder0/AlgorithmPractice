#include <cstdio>
using namespace std;
int n;
char all[(1<<10) + 10];
int build(int l,int r)//-1为I串(1)，1为B串(0)，0为F串(01)
{
    if(l == r)
    {
        if(all[l] == '0')
        {
            putchar('B');
            return 1;
        }
        else
        {
            putchar('I');
            return -1;
        }
    }
    int mid = (l+r)>>1;
    int ans2 = build(l,mid);
    int ans1 = build(mid+1,r);
    if(ans1 == ans2)
    {
        if(ans1 == -1)
            putchar('I');
        else if(ans1 == 1)
            putchar('B');
        else
            putchar('F');
        return ans1;
    }
    putchar('F');
    return 0;
}
int main()
{
    scanf("%d",&n);
    scanf("%s",all+1);
    build(1,1<<n);
    return 0;
}