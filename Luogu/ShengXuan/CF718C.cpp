#include <cstdio>
#include <cstring>
const int mod = 1e9 + 7;
inline int add(int a,int b){int t = a + b;return t >= mod ? t - mod : t;}
inline int mul(int a,int b){long long t = 1ll * a * b;return t >= mod ? t % mod : t;}
struct matrix
{
	int n,m,a[4][4];
	matrix(){std::memset(a,0,sizeof(a));}
	matrix(int _n,int _m){n = _n,m = _m,std::memset(a,0,sizeof(a));}
	matrix operator*(const matrix b)
	{
		matrix c;
		c.n = n,c.m = b.m;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) for(int k = 1;k<=b.m;++k) c.a[i][k] = add(c.a[i][k],mul(a[i][j],b.a[j][k]));
		return c;
	}
	matrix operator+(const matrix b)
	{
		matrix c;
		c.n = n,c.m = m;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) c.a[i][j] = add(a[i][j],b.a[i][j]);
		return c;
	}
}A,B[70];
const int maxn = 1e5 + 100;
int n,m,a[maxn];
#define ls p << 1
#define rs p << 1 | 1
matrix mat[maxn << 2],multag[maxn << 2];
bool needmul[maxn << 2];
inline void pushup(int p){mat[p] = mat[ls] + mat[rs];}
inline void pushmul(int p,const matrix&k)
{
	mat[p] = mat[p] * k;
	if(!needmul[p]) multag[p] = k; else multag[p] = multag[p] * k;
	needmul[p] = 1;
}
inline void pushdown(int p)
{
	if(!needmul[p]) return;
	pushmul(ls,multag[p]),pushmul(rs,multag[p]);
	needmul[p] = 0;
}
matrix ask(int l,int r,int p,int ll,int rr)
{
	if(l >= ll && r <= rr) return mat[p];
	int mid = (l + r) >> 1;
	matrix res(1,3);
	pushdown(p);
	if(ll <= mid) res = res + ask(l,mid,ls,ll,rr);
	if(rr > mid) res = res + ask(mid + 1,r,rs,ll,rr);
	return res;
}
void modify(int l,int r,int p,int ll,int rr,const matrix &k)
{
	if(l >= ll && r <= rr) return (void)(pushmul(p,k));
	int mid = (l + r) >> 1;
	pushdown(p);
	if(ll <= mid) modify(l,mid,ls,ll,rr,k);
	if(rr > mid) modify(mid + 1,r,rs,ll,rr,k);
	pushup(p);
}
void build(int l,int r,int p)
{
	if(l == r)
	{
		mat[p] = A;
		for(int k = 0;(1 << k) <= a[l];++k) if((a[l] >> k) & 1) mat[p] = mat[p] * B[k];
		return;
	}
	int mid = (l + r) >> 1;
	build(l,mid,ls),build(mid + 1,r,rs),pushup(p);
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1;i<=n;++i) scanf("%d",a + i),--a[i];
	A.n = 1,A.m = 2,A.a[1][1] = 0,A.a[1][2] = 1;//f(1)
	B[0].n = 2,B[0].m = 2,B[0].a[1][2] = 1,B[0].a[2][1] = 1,B[0].a[2][2] = 1;
	for(int i = 1;i<=64;++i) B[i] = B[i-1] * B[i-1];
	build(1,n,1);
	for(int i = 1,opt,l,r,x;i<=m;++i)
	{
		scanf("%d %d %d",&opt,&l,&r);
		if(opt == 1) 
		{
			scanf("%d",&x);
			matrix C = B[0];
			--x;
			for(int k = 0;(1 << k) <= x;++k) if((x >> k) & 1) C = C * B[k];
			modify(1,n,1,l,r,C);
		}
		else 
		{
			matrix res = ask(1,n,1,l,r);
			printf("%d\n",res.a[1][2]);
		}
		
	}
	return 0;
}
