#include <iostream>
#include <string>
using namespace std;
int T,n,k;
string s,f[510];
inline char up(char c){return c == ('a' + k - 1) ? 'a' : c + 1;}
inline char down(char c){return c == 'a' ? 'a' + k - 1 : c - 1;}
inline void chkmin(string &a,string b)
{
	if(a.empty()) a = b;
	a = min(a,b);
}
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> n >> k;
		cin >> s;
		for(int i = 0;i<=n;++i) f[i] = string();
		f[0] = f[0] + min(s[0],min(up(s[0]),down(s[0])));
		f[1] = f[0] + min(s[1],min(up(s[1]),down(s[1])));
		string t;t = t + s[1] + s[0];
		t[0] = min(t[0],min(up(t[0]),down(t[0])));
		f[1] = min(f[1],t);
		for(int i = 0;i + 1 <n;++i)
		{
			//normal
			chkmin(f[i+1],f[i] + min(s[i+1],min(up(s[i+1]),down(s[i+1]))));
			//left
			string t = f[i] + s[i+1];
			//cout << t << '\n';
			std::swap(t[i],t[i+1]);
			//cout << t << '\n';
			chkmin(f[i+1],t);
			if(i + 2 >= n) continue;
			//right and normal
			t = f[i] + min(s[i+2],min(up(s[i+2]),down(s[i+2]))) + s[i+1];
			chkmin(f[i+2],t);
			//right and left
			t = f[i] + s[i+2] + s[i+1];
			std::swap(t[i],t[i+1]);
			chkmin(f[i+2],t);
			//cout << f[i] << '\n';
		}
		cout << f[n - 1] << '\n';
	}
	return 0;
}
