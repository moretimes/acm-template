#include <cstdio>
#include <set>
#include <map>

using namespace std;

const int N = 100000 + 10;
const int inf = 100001;
const double eps = 1e-10;

set<int> S;
int B[N];
double xval[N];
map<double, int> X;

void cal(int a1, int b1, int a2, int b2, double& x, double& y) {
	if (a2 == -inf) {
		x = 0;
		y = b1;
	}
	else {
		x = (b2 - b1) / double(a1 - a2);
		y = a1 * x + b1;
	}
}

int main() {
	int n, a, b, i;
	double x, y;
	char cmd[2];
	set<int>::iterator itr;
	S.insert(-inf);
	S.insert(0);
	B[inf] = 0;
	xval[inf] = inf;
	B[0] = 0;
	X[0] = 0;
	xval[0] = 0;
	scanf("%d", &n);
	for (i=1; i<=n; i++) {
		scanf("%s", cmd);
		if (cmd[0] == 'S') {
			scanf("%d %d", &a, &b);
			itr = S.lower_bound(a);
			if (*itr == a) {
				if (B[-*itr] >= b) continue; else B[-*itr] = b;
			}
			else {
				itr --;
				cal(a, b, *itr, B[-*itr], x, y);
				itr ++;
				if (y < *itr * x + B[-*itr] + eps) continue;
				itr = S.insert(a).first;
				B[-*itr] = b;
			}
			itr --;
			while (itr != S.begin() && *itr * xval[-*itr] + B[-*itr] < a * xval[-*itr] + b + eps) {
				x = xval[-*itr];
				X.erase(x);
				S.erase(itr --);
			}
			cal(a, b, *itr, B[-*itr], x, y);
			itr = S.find(a);
			itr ++;
			X.erase(xval[-*itr]);
			xval[-a] = x;
			X[x] = a;
			itr ++;
			while (itr != S.end() && *itr * xval[-*itr] + B[-*itr] < a * xval[-*itr] + b + eps) {
				itr --;
				S.erase(itr ++);
				x = xval[-*itr];
				X.erase(x);
				itr ++;
			}
			itr --;
			cal(a, b, *itr, B[-*itr], x, y);
			xval[-*itr] = x;
			X[x] = *itr;
		}
		else {
			scanf("%lf", &x);
			x = x * x;
			map<double, int>::iterator itr;
			if (x == 0) itr = X.lower_bound(0);
			else {
				itr = X.lower_bound(x);
				itr --;
			}
			printf("%.0lf\n", itr->second * x + B[-itr->second]);
		}
	}
	return 0;
}                                 
