#include <cstdio>
#include <algorithm>
using namespace std;
int n,a[4],b[4],ta[4],tb[4];
pair<int,int> order[7];
int main()
{
    scanf("%d",&n);
    scanf("%d %d %d", a + 1, a + 2, a + 3);
    scanf("%d %d %d", b + 1, b + 2, b + 3);
    int maxwin = min(a[1], b[2]) + min(a[2], b[3]) + min(a[3], b[1]);
    order[1] = make_pair(1,1);
    order[2] = make_pair(1,3);
    order[3] = make_pair(2,2);
    order[4] = make_pair(2,1);
    order[5] = make_pair(3,3);
    order[6] = make_pair(3,2);
    int minwin = 1<<30;
    do
    {
        int tmp = 0;
        ta[1] = a[1], ta[2] = a[2], ta[3] = a[3], tb[1] = b[1], tb[2] = b[2], tb[3] = b[3];
        for (int i = 1; i <= 6; ++i)
        {
            int l = order[i].first,r = order[i].second;
            int t = min(ta[l], tb[r]);
            tmp += t, ta[l] -= t, tb[r] -= t;
        }
        minwin = min(minwin,n - tmp);
    }while(next_permutation(order + 1,order + 7));
    printf("%d %d",minwin,maxwin);
    return 0;
}