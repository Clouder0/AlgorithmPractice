 #include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 3e5 + 100;
int n;
long long sum[maxn][2];
void solve(vector<int> v, int bit)
{
    if (v.empty() || bit < 0) return;
    vector<int> zero, one;
    long long zeronum = 0, onenum = 0;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        if (*it & (1 << bit)) one.push_back(*it), onenum += zero.size();
        else zero.push_back(*it) , zeronum += one.size();
    sum[bit][0] += zeronum, sum[bit][1] += onenum;
    solve(zero, bit - 1), solve(one, bit - 1);
}
int main()
{
    scanf("%d",&n);
    vector<int> v;
    for (int i = 1, x; i <= n; ++i) scanf("%d", &x), v.push_back(x);
    solve(v, 30);
    long long res = 0;
    int x = 0;
    for (int i = 30; i >= 0; --i)
        if (sum[i][0] <= sum[i][1]) res += sum[i][0];
        else res += sum[i][1], x += (1 << i);
    printf("%lld %d\n", res, x);
    return 0;
}