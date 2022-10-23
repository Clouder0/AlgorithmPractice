#include <cstdio>
using namespace std;
const int maxn = 20;
const int maxm = (1<<18) + 100;
int n,q,a[maxm];
int rev[maxn];
long long sum[maxm<<2];
void build(int l,int r,int p)
{
	if(l == r)
	{
		sum[p] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
	sum[p] = sum[p<<1] + sum[p<<1|1];
}
void modify(int l,int r,int p,int pos,int k,int dep)
{
	if(l == r) return (void)(sum[p] = k);
	int mid = l + r >> 1;
	if(pos <= mid) modify(l,mid,p<<1|rev[dep],pos,k,dep-1);
	else modify(mid + 1,r,p<<1|(!rev[dep]),pos,k,dep-1);
	sum[p] = sum[p<<1] + sum[p<<1|1];
}
long long ask(int l,int r,int p,int ll,int rr,int dep)
{
	if(l >= ll && r <= rr) return sum[p];
	int mid = l + r >> 1;
	long long res = 0;
	if(ll <= mid) res = ask(l,mid,(p<<1)|rev[dep],ll,rr,dep-1);
	if(rr > mid) res += ask(mid + 1,r,(p<<1)|(!rev[dep]),ll,rr,dep-1);
	return res;
}
void reverse(int k){for(int i = 0;i<=k;++i) rev[i]^=1;}
int main()
{
	scanf("%d %d",&n,&q);
	int nn = 1<<n;
	for(int i = 1;i<=nn;++i) scanf("%d",a + i);
	build(1,nn,1);
	while(q--)
	{
		int opt;
		scanf("%d",&opt);
		if(opt == 1)
		{
			int x,k;
			scanf("%d %d",&x,&k);
			modify(1,nn,1,x,k,n);
		}
		else if(opt == 2)
		{
			int k;
			scanf("%d",&k);
			reverse(k);
		}
		else if(opt == 3)
		{
			int k;
			scanf("%d",&k);
			rev[k+1]^=1;
		}
		else 
		{
			int l,r;
			scanf("%d %d",&l,&r);
			printf("%lld\n",ask(1,nn,1,l,r,n));
		}
	}
	return 0;
}
