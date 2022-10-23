#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int n, m, k;
int H[2 * maxn],hcnt;
struct point
{
	int x,y,num;
}A[maxn];
bool cmp(const point &a, const point &b)
{
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}
int sum[maxn], f[maxn];
inline void add(int x, int k){ for(; x <= hcnt; x += x & -x) sum[x] = std::max(sum[x],k);}
inline int ask(int x){int res = 0; for(; x > 0; x -= x & -x) res = std::max(res,sum[x]); return res;}
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1; i <= k; ++i) scanf("%d %d %d", &A[i].x, &A[i].y, &A[i].num), H[++hcnt] = A[i].y;
	sort(H + 1, H + 1 + hcnt), hcnt = unique(H + 1, H + 1 + hcnt) - H - 1;
	for(int i = 1; i <= k; ++i) A[i].y = lower_bound(H + 1, H + 1 + hcnt, A[i].y) - H;
	sort(A + 1,A + 1 + k,cmp);
	int ans = 0;
	for(int i = 1; i <= k; ++i)  f[i] = ask(A[i].y) + A[i].num, add(A[i].y, f[i]), ans = std::max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
