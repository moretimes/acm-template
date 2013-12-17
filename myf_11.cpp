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
typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
typedef pair<LL,int> PLI;
typedef vector<int> VI;
typedef LL T;

const int N=50005,M=1<<16;

int n,m,q,tot;
int v[N];
int t[M*2];
VI E[N];
int fa[N],dep[N],son[N],sz[N];
int id[N],top[N];

void dfs(int x){
    sz[x]=1,son[x]=0;
    rep(i,E[x].size()){
        int y=E[x][i];
        if (y==fa[x]) continue;
        dep[y]=dep[x]+1;
        fa[y]=x;
        dfs(y);
        sz[x]+=sz[y];
        if (sz[y]>sz[son[x]]) son[x]=y;
    }
}

void dfs(int x,int p){
    id[x]=++tot,top[x]=p;
    if (son[x]) dfs(son[x],p);
    rep(i,E[x].size()){
        int y=E[x][i];
        if (y==fa[x]||y==son[x]) continue;
        dfs(y,y);
    }
}

int ask(int x){
    x=id[x];
    int ret=0;
    for(x+=M;x;x>>=1) ret+=t[x];
    return ret;
}

void insert(int l,int r,int x){
    for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1){
        if (~l&1) t[l^1]+=x;
        if ( r&1) t[r^1]+=x;
    }
}

void add(int x,int y,int k){
    while(top[x]!=top[y]){
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        insert(id[top[x]],id[x],k);
        x=fa[top[x]];
    }
    if (dep[x]<dep[y]) swap(x,y);
    insert(id[y],id[x],k);
}

int main(){
    while(~scanf("%d%d%d",&n,&m,&q)){
        rep(i,n) scanf("%d",&v[i+1]);
        rep(i,n) E[i+1].clear();
        rep(i,m){
            int x,y;
            scanf("%d%d",&x,&y);
            E[x].PB(y);
            E[y].PB(x);
        }
        fa[1]=dep[1]=1;
        sz[0]=0,tot=0;
        dfs(1);
        dfs(1,1);
        Cls(t);
        fab(i,1,n) t[id[i]+M]=v[i];
        char ch;
        int x,y,k;
        rep(i,q){
            while((ch=getchar())&&ch!='D'&&ch!='Q'&&ch!='I');
            if (ch=='Q'){
                scanf("%d",&x);
                printf("%d\n",ask(x));
            }
            else{
                scanf("%d%d%d",&x,&y,&k);
                add(x,y,(ch=='I')?k:-k);
            }
        }
    }
    return 0;
}
