#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>
const int bufSize = 1e6;
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize],*p1 = buf,*p2 = buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
T read(T &r)
{
	static char c;
	r = 0;
	for(c=nc();!isdigit(c);c=nc());
	for(;isdigit(c);c=nc()) r = r*10+c-48;
	return r;
}
const int mod = 1e9 + 7;
inline int add(const int &a,const int &b){int t = a + b;return t >= mod ? t - mod : t;}
inline int mul(const int &a,const int &b){long long t = 1ll * a * b;return t >= mod ? t % mod : t;}
const int maxn = 4e6 + 100;
int n, m, a[maxn], sz[maxn], L[maxn], R[maxn], val[maxn], sum[maxn], addtag[maxn], settag[maxn], revtag[maxn], root, ind;
inline int rnd(){return rand();}
inline int newnode(int v = 0)
{
	int x = ++ind;
	sz[x] = 1, L[x] = R[x] = addtag[x] = revtag[x] = 0, sum[x] = val[x] = v, settag[x] = -1;
	return x;
}
inline int copy(int y)
{
	if(!y) return 0;
	int x = ++ind;
	sz[x] = sz[y],L[x] = L[y],R[x] = R[y],val[x] = val[y],sum[x] = sum[y],addtag[x] = addtag[y],settag[x] = settag[y],revtag[x] = revtag[y];
	return x;
}
#define ls L[p]
#define rs R[p]
inline void pushup(int p) { sz[p] = sz[ls] + sz[rs] + 1, sum[p] = add(val[p],add(sum[ls], sum[rs])); }
inline void pushset(int p,int k){if(p) addtag[p] = 0,val[p] = k,settag[p] = k,sum[p] = mul(sz[p],k);}
inline void pushadd(int p,int k){if(p) val[p] = add(val[p],k),addtag[p] = add(addtag[p],k),sum[p] = add(sum[p],mul(k,sz[p]));}
inline void pushdown(int p)
{
	if(!revtag[p] && !addtag[p] && settag[p] == -1) return;
	ls = copy(ls),rs = copy(rs);
	if(revtag[p]) std::swap(ls,rs),revtag[ls] ^= 1,revtag[rs] ^= 1, revtag[p] = 0;
	if(settag[p] != -1) pushset(ls,settag[p]),pushset(rs,settag[p]),settag[p] = -1;
	if(addtag[p]) pushadd(ls,addtag[p]),pushadd(rs,addtag[p]),addtag[p] = 0;
}
void split(int p, int k, int &x, int &y)
{
	if(!p) return (void)(x = y = 0);
	pushdown(p);
	if(k <= sz[ls]) y = copy(p),split(L[y],k,x,L[y]),pushup(y);
	else x = copy(p),split(R[x],k-sz[ls]-1,R[x],y),pushup(x);
}
int merge(int x,int y)
{
	if(!x || !y) return x + y;
	if(rnd() % (sz[x] + sz[y]) < sz[x]) return pushdown(x),x = copy(x), R[x] = merge(R[x],y),pushup(x),x;
	return pushdown(y),y = copy(y), L[y] = merge(x,L[y]),pushup(y),y;
}
int asksum(int l,int r)
{
	int s,m,b,res;
	split(root,r,m,b),split(m,l-1,s,m),res = sum[m],root = merge(s,merge(m,b));
	return res;
}
void seqset(int l,int r,int k)
{
	int s,m,b;
	split(root,r,m,b),split(m,l-1,s,m);
	pushset(m,k);
	root = merge(s,merge(m,b));
}
void seqadd(int l,int r,int k)
{
	int s,m,b;
	split(root,r,m,b),split(m,l-1,s,m);
	pushadd(m,k);
	root = merge(s,merge(m,b));
}
void seqcopy(int l1,int r1,int l2,int r2)
{
	int swapped = 0;
	if(l1 > r2) std::swap(l1,l2),std::swap(r1,r2),swapped = 1;
	int a,b,c,d,e;
	split(root,r2,d,e);
	split(d,l2-1,c,d);
	split(c,r1,b,c);
	split(b,l1-1,a,b);
	if(swapped) b = copy(d); else d = copy(b);
	root = merge(a,merge(b,merge(c,merge(d,e))));
}
void seqswap(int l1,int r1,int l2,int r2)
{
	if(l1 > r2) std::swap(l1,l2),std::swap(r1,r2);
	int a,b,c,d,e;
	split(root,r2,d,e),split(d,l2-1,c,d),split(c,r1,b,c),split(b,l1-1,a,b);
	std::swap(b,d);
	root = merge(a,merge(b,merge(c,merge(d,e))));
}
void seqreverse(int l,int r)
{
	int s,m,b;
	split(root,r,m,b),split(m,l-1,s,m),revtag[m] ^= 1,root = merge(s,merge(m,b));
}
void clear(){ind = 0;}
int build(int l,int r)
{
	if(l > r) return 0;
	if(l == r) return newnode(a[l]);	
	int mid = (l + r) >> 1,p = newnode(a[mid]);
	ls = build(l,mid - 1),rs = build(mid + 1,r),pushup(p);
	return p;
}
int num;
void reversebuild(int p)
{
	if(!p) return;
	pushdown(p),reversebuild(ls),a[++num] = val[p],reversebuild(rs);
}
inline void rebuild(){num = 0,reversebuild(root),clear(),root = build(1,n);}
int main()
{
	srand(time(0));
	read(n),read(m);
	for(int i = 1;i<=n;++i) read(a[i]);
	root = build(1,n);
//	int rebuildfrac = std::max(100,m / 10);
    //int rebuildfrac = std::max(100,m/10);
    int step = std::max(100,m / 20);
    int rebuildfrac = step;
	for(int i = 1,opt,l1,r1,l2,r2,k;i<=m;++i)
	{
		read(opt),read(l1),read(r1);
		if(opt == 1) printf("%d\n",asksum(l1,r1));
		else if(opt == 2) read(k),seqset(l1,r1,k);
		else if(opt == 3) read(k),seqadd(l1,r1,k);
		else if(opt == 4) read(l2),read(r2),seqcopy(l1,r1,l2,r2);
		else if(opt == 5) read(l2),read(r2),seqswap(l1,r1,l2,r2);
		else seqreverse(l1,r1);
		if(i == rebuildfrac) rebuild(),rebuildfrac += step;
		//printf(":%d-th:\n",i);
		//num = 0,reversebuild(root);
		//for(int i = 1;i<=n;++i) printf("%d ",a[i]);
		//puts("");
	}
	num = 0,reversebuild(root);
	for(int i = 1;i<=n;++i) printf("%d ",a[i]);
	return 0;
}

