#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 4e5 + 100;
struct node
{
	int opt,pos,val;
}A[maxn];
int n,m,a[maxn],H[maxn],cnt;
int sum[maxn];
inline void add(int x,int k) { for(++x;x <= cnt + 10;x+=x&-x) sum[x] += k;}
inline void addrange(int l,int r,int k){add(l,k),add(r+1,-k);}
inline int ask(int x){int res = 0;for(++x;x>0;x-=x&-x) res += sum[x];return res;}
inline void update(int x,int k)
{
	int minn = min(a[x],a[x+1]);
	addrange(1,minn,-k);
}
int main()
{
	scanf("%d %d",&n,&m);
	H[++cnt] = 1 << 30;
	for(int i = 1;i<=n;++i) scanf("%d",a + i),H[++cnt] = a[i];
	for(int i = 1;i<=m;++i)
	{
		scanf("%d",&A[i].opt);
		if(A[i].opt == 1) scanf("%d",&A[i].val),H[++cnt] = A[i].val;
		else scanf("%d %d",&A[i].pos,&A[i].val),H[++cnt] = A[i].val;
	}
	std::sort(H + 1,H + 1 + cnt),cnt = std::unique(H + 1,H + 1 + cnt) - H - 1;
	for(int i = 1;i<=n;++i) a[i] = lower_bound(H + 1,H + 1 + cnt,a[i]) - H;
	for(int i = 1;i<=m;++i) A[i].val = lower_bound(H + 1,H + 1 + cnt,A[i].val) - H;
	for(int i = 1;i<=n;++i) addrange(1,a[i],1);
	for(int i = 1;i<n;++i) update(i,1);
	for(int i = 1;i<=m;++i)
	{
		if(A[i].opt == 1) printf("%d\n",ask(A[i].val));
		else
		{
			int p = A[i].pos,v = A[i].val;
			add(a[p] + 1,1),add(v + 1,-1);
			update(p - 1,-1),update(p,-1);
			a[p] = v;
			update(p-1,1),update(p,1);
		}
	}
	return 0;
}
