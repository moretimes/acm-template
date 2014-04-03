// vertices numbered from 1 to N
// No self-loops and no duplicate edges

typedef pair<int, int> T;
const int maxn = 10000 + 10;

struct node {
	int dep, fa, infc, used, vst, dfi, ec, lowp, bflag, flag, lowpoint;
};

int n, m, indee, p1, p2, p, ps;
int lk[maxn * 3][2], child[maxn * 3][3], bedg[maxn * 3][2], sdlist[maxn * 6][3], 
	buk[maxn * 6][2], exf[maxn * 3][2], proots[maxn * 3][3], stk[maxn * 3][2], infap[maxn * 3];
int w1[maxn], w2[maxn], que[maxn];
node dot[maxn];

void init(T * ts) {
	ps = 0;
	for (int i = 1; i <= n; ++i) w1[i] = i;
	p1 = n;
	for (int i = 0; i < m; ++i) {
		int k1 = ts[i].first, k2 = ts[i].second;
		lk[++p1][0] = k2; lk[p1][1] = 0;
		lk[w1[k1]][1] = p1;
		w1[k1] = p1;
		lk[++p1][0] = k1; lk[p1][1] = 0;
		lk[w1[k2]][1] = p1;
		w1[k2] = p1;
	}
	for (int i = 1; i <= n; ++i) que[i] = i;
}

int deep(int a) {
	dot[a].used = 1; dot[a].dfi = ++indee;
	int t = lk[a][1];
	while (t != 0) {
		int tmp = lk[t][0];
		if (!dot[tmp].used) {
			dot[tmp].fa = a; dot[tmp].dep = dot[a].dep + 1; dot[tmp].ec = dot[a].dep; dot[tmp].lowp = dot[a].dep;
			child[++p1][0] = tmp; child[p1][1] = 0;
			child[w1[a]][1] = p1;
			w1[a] = p1;
			int s = deep(tmp);
			if (s < dot[a].ec) dot[a].ec = s;
		}
		else if (dot[a].fa != tmp) {
			if (dot[a].lowp > dot[tmp].dep) dot[a].lowp = dot[tmp].dep;
			if (dot[a].dfi > dot[tmp].dfi) {
				bedg[++p2][0] = a; bedg[p2][1] = 0;
				bedg[w2[tmp]][1] = p2;
				w2[tmp] = p2;
			}
		}
		t = lk[t][1];
	}
	if (dot[a].ec > dot[a].lowp) dot[a].ec = dot[a].lowp;
	return dot[a].ec;
}

void sortvtx() {
	for (int i = 1; i <= n; ++i) w1[i] = i;
	p1 = n; p2 = 0;
	for (int i = 1; i <= n; ++i) {
		buk[++p1][0] = i; buk[p1][1] = 0;
		buk[w1[dot[i].dfi]][1] = p1;
		w1[dot[i].dfi] = p1;
	}
	for (int i = n; i > 0; --i) {
		int tmp = buk[i][1];
		while (tmp != 0) {
			que[++p2] = buk[tmp][0];
			tmp = buk[tmp][1];
		}
	}
}

void getsdlist() {
	memset(buk, 0, sizeof(buk));
	for (int i = 1; i <= n; ++i) {
		w1[i] = w2[i] = i;
		buk[i][1] = 0;
	}
	p1 = p2 = n;
	for (int i = 1; i <= n; ++i) {
		buk[++p1][0] = i; buk[p1][1] = 0;
		buk[w1[dot[i].ec]][1] = w1[dot[i].ec] = p1;
	}
	for (int i = 1; i <= n; ++i) {
		int tmp = buk[i][1];
		while (tmp != 0) {
			int fa = dot[buk[tmp][0]].fa;
			sdlist[++p2][0] = i; sdlist[p2][1] = 0;
			sdlist[w2[fa]][1] = dot[buk[tmp][0]].infc = p2;
			sdlist[p2][2] = w2[fa]; w2[fa] = p2;
			tmp = buk[tmp][1];
		}
	}
}

void getnextvtx(int v, int v1, int &m, int &m1) {
	m = exf[v][v1 ^ 1];
	if (exf[m][0] == v) m1 = 0;
	else m1 = 1;
}

void addwei(int a) {
	int fa = dot[a - n].fa;
	++p1;
	proots[p1][0] = a; proots[p1][1] = 0;
	proots[w1[fa]][1] = p1;
	proots[p1][2] = w1[fa]; w1[fa] = p1;
	infap[a] = p1;
}

void addsou(int a) {
	int fa = dot[a - n].fa;
	++p1;
	proots[p1][0] = a; proots[p1][1] = proots[fa][1]; proots[p1][2] = fa;
	proots[fa][1] = p1;
	proots[proots[p1][1]][2] = p1;
	infap[a] = p1;
	if (w1[fa] == fa) w1[fa] = p1;
}

void walkup(int v, int w) {
	dot[w].bflag = v;
	int x = w, x1 = 1, y = w, y1 = 0;
	while (x != v) {
		if (dot[x].vst == v || dot[y].vst == v) break;
		dot[x].vst = v; dot[y].vst = v;
		int z1 = 0;
		if (x > n) z1 = x;
		if (y > n) z1 = y;
		if (z1 != 0) {
			int c = z1 - n, z = dot[c].fa;
			if (z != v) {
				if (dot[c].lowpoint < dot[v].dep) addwei(z1);
				else addsou(z1);
			}
			x = z; x1 = 1;
			y = z; y1 = 0;
		} else {
			getnextvtx(x, x1, x, x1);
			getnextvtx(y, y1, y, y1);
		}
	}
}

void getactivenext(int v, int v1, int &m, int &m1, int vt) {
	m = v; m1 = v1;
	getnextvtx(m, m1, m, m1);
	while (dot[m].bflag != vt && proots[m][1] == 0 && dot[m].ec >= dot[vt].dep && m != v) getnextvtx(m, m1, m, m1);
}

void addstack(int a, int b) {
	stk[++ps][0] = a; stk[ps][1] = b;
}

void mergestack() {
	int t = stk[ps][0], t1 = stk[ps][1], k = stk[ps - 1][0], k1 = stk[ps - 1][1];
	ps -= 2;
	int s1, s = exf[t][1 ^ t1];
	if (exf[s][1] == t) s1 = 1;
	else s1 = 0;
	exf[k][k1] = s;
	exf[s][s1] = k;
	int tmp = dot[t - n].infc;
	sdlist[sdlist[tmp][2]][1] = sdlist[tmp][1]; sdlist[sdlist[tmp][1]][2] = sdlist[tmp][2];
	tmp = dot[t - n].fa;
	if (sdlist[tmp][1] == 0) dot[tmp].ec = dot[tmp].lowp;
	else dot[tmp].ec = min(dot[tmp].lowp, sdlist[sdlist[tmp][1]][0]);
	tmp = infap[t];
	int fa = dot[t - n].fa;
	proots[proots[tmp][2]][1] = proots[tmp][1];
	if (proots[tmp][1] != 0) proots[proots[tmp][1]][2] = proots[tmp][2];
	else w1[fa] = proots[tmp][2];
}

void embededg(int v, int v1, int w, int w1) {
	exf[v][v1] = w; exf[w][w1] = v;
}

void walkdown(int v) {
	ps = 0;
	int vt = dot[v - n].fa;
	for (int v2 = 0; v2 <= 1; ++v2) {
		int w, w1;
		getnextvtx(v, 1 ^ v2, w, w1);
		while (w != v) {
			if (dot[w].bflag == vt) {
				while (ps != 0) mergestack();
				embededg(v, v2, w, w1);
				dot[w].bflag = 0;
			}
			if (proots[w][1] != 0) {
				addstack(w, w1);
				int x, x1, y, y1, w2, w0 = proots[proots[w][1]][0];
				getactivenext(w0, 1, x, x1, vt);
				getactivenext(w0, 0, y, y1, vt);
				if (dot[x].ec >= dot[vt].dep) w = x, w1 = x1;
				else if (dot[y].ec >= dot[vt].dep) w = y, w1 = y1;
				else if (dot[x].bflag == vt || proots[x][1] != 0) w = x, w1 = x1;
				else w = y, w1 = y1;
				if (w == x) w2 = 0;
				else w2 = 1;
				addstack(w0, w2);
			}
			else if (w > n || dot[w].ec >= dot[vt].dep) getnextvtx(w, w1, w, w1);
			else {
				if (w <= n && dot[w].ec < dot[vt].dep && ps == 0) embededg(v, v2, w, w1);
				break;
			}
		}
		if (ps != 0) break;
	}
}

bool chainvtx(int a) {
	for (int t = child[a][1]; t != 0; t = child[t][1]) {
		int tmp = child[t][0];
		exf[tmp][1] = tmp + n; exf[tmp][0] = tmp + n;
		exf[tmp + n][1] = tmp; exf[tmp + n][0] = tmp;
	}
	for (int t = bedg[a][1]; t != 0; t = bedg[t][1]) walkup(a, bedg[t][0]);
	for (int t = child[a][1]; t != 0; t = child[t][1]) walkdown(child[t][0] + n);
	for (int t = bedg[a][1]; t != 0; t = bedg[t][1]) if (dot[bedg[t][0]].bflag != 0) return false;
	return true;
}

bool judge(int N, int M, T * ts) {
	n = N;	m = M;
	if (n == 1) return true;
	if (m > 3 * n - 5) return false;
	init(ts);
	
	for (int i = 1; i <= n; ++i) {
		proots[i][1] = 0; proots[i + n][1] = 0;
		p = 0;
		child[i][1] = 0;
		buk[i][1] = 0; buk[i + n][1] = 0;
		sdlist[i][1] = 0; sdlist[i + n][1] = 0;
		dot[i].bflag = 0; dot[i + n].flag = 0;
	}
	for (int i = 1; i <= n; ++i) {
		w1[i] = i; w2[i] = i;
		child[i][1] = 0; bedg[i][1] = 0;
		dot[i].used = 0;
	}
	indee = 0; p1 = p2 = n;
	for (int i = 1; i <= n; ++i) {
		if (!dot[i].used) {
			dot[i].dep = 1;
			deep(i);
		}
	}
	sortvtx();
	getsdlist();
	for (int i = 1; i <= n; ++i) {
		dot[i].lowpoint = dot[i].ec;
		dot[i].vst = 0; dot[i + n].vst = 0;
		proots[i][1] = 0;
		w1[i] = i;
	}
	p1 = n;
	for (int i = 1; i <= n; ++i) if (!chainvtx(que[i])) return false;
	return true;
}

T ts[maxn];
bool a[3001][3001];

int main() {
	int N, M;
	scanf("%d%d", &N, &M);
	int m = 0;
	for(int i = 0; i < M; i ++) {
		scanf("%d%d", &ts[i].first, &ts[i].second);
		++ts[i].first; ++ts[i].second;
		if (ts[i].first == ts[i].second || a[ts[i].first][ts[i].second]) continue;
		a[ts[i].first][ts[i].second] = a[ts[i].second][ts[i].first] = 1;
		ts[m++] = ts[i];
	}
	M = m;
	if(judge(N, M, ts)) puts("YES");
	else puts("NO");

	return 0;
}
