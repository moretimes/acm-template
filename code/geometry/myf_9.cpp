//By myf
//#pragma comment(linker, "/STACK:16777216")  //C++
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <complex>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <list>

#define rep(i,n) for(int i=0;i<(n);i++)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define fab(i,a,b) for(int i=(a);i<=(b);i++)
#define fba(i,b,a) for(int i=(b);i>=(a);i--)
//#define foreach(i,n) for(__typeof(n.begin()) i=n.begin();i!=n.end();i++) //G++
#define MP make_pair
#define PB push_back
#define X first
#define Y second
#define Cls(x) memset(x,0,sizeof x)
#define Print(n,x) for(int i=0;i<(n);i++) cout<<x<<" ";cout<<endl;
#define Sqr(x) (x)*(x)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
typedef pair<LL,int> PLI;
typedef vector<int> VI;
typedef LL T;

const int N = 500005,K = 2,D=6;
const LL inf = ((ULL)1<<63)-1;
//const int inf=~0U>>1;

struct kd{
    T x[K];
    kd(){rep(i,K)x[i]=0;}
} t[N];
int l[N],r[N];
int a[D],n,tot,root;

void insert(int &cur,kd p, int d) {
    if (!cur){
        cur=++tot;
        rep(i,K) t[cur].x[i] = p.x[i];
        l[cur]=r[cur]=0;
        return;
    }
    T dx = p.x[d] - t[cur].x[d];
    if (++d==K) d=0;
    insert(dx<0?l[cur]:r[cur],p,d);
}

T dis2(kd a,kd b) {
    T s=0;
    rep(i,K) s+=Sqr(a.x[i]-b.x[i]);
    return s;
}

void query(int cur, kd p, LL &ret, int d) {
    if (!cur) return;
    ret = min(ret, dis2(t[cur],p));
    T dx = p.x[d] - t[cur].x[d];
	if (++d == K) d = 0;
	if (dx < 0) {
	    query(l[cur],p,ret,d);
		if (ret > Sqr(dx)) query(r[cur],p,ret,d);
	} else {
	    query(r[cur],p,ret,d);
		if (ret > Sqr(dx)) query(l[cur],p,ret,d);
	}
}

void work() {
    root = tot = 0;
    T ans = inf, ret=0;
    kd p;
    rep(i,n){
        p.x[0] = (p.x[0] * a[0] + a[1]) % a[2];
        p.x[1] = (p.x[1] * a[3] + a[4]) % a[5];
        query(root, p, ans, 0);
        insert(root, p, 0);
        ret += ans * (i > 0);
    }
    printf("%I64d\n", ret);
}

int main() {
    int test;
    scanf("%d", &test);
    rep(cas,test){
        scanf("%d", &n);
        rep(i,D) scanf("%d", &a[i]);
        work();
    }
    return 0;
}