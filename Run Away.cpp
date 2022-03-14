/*描述
One of the traps we will encounter in the Pyramid is located in the Large Room. A lot of small holes are drilled into the floor. They look completely harmless at the first sight. But when activated, they start to throw out very hot java, uh ... pardon, lava. Unfortunately, all known paths to the Center Room (where the Sarcophagus is) contain a trigger that activates the trap. The ACM were not able to avoid that. But they have carefully monitored the positions of all the holes. So it is important to find the place in the Large Room that has the maximal distance from all the holes. This place is the safest in the entire room and the archaeologist has to hide there.
输入
The input consists of T test cases. The number of them (T) is given on the first line of the input file. Each test case begins with a line containing three integers X, Y, M separated by space. The numbers satisfy conditions: 1 <= X,Y <=10000, 1 <= M <= 1000. The numbers X and Yindicate the dimensions of the Large Room which has a rectangular shape. The number M stands for the number of holes. Then exactly M lines follow, each containing two integer numbers Ui and Vi (0 <= Ui <= X, 0 <= Vi <= Y) indicating the coordinates of one hole. There may be several holes at the same position.
输出
Print exactly one line for each test case. The line should contain the sentence "The safest point is (P, Q)." where P and Qare the coordinates of the point in the room that has the maximum distance from the nearest hole, rounded to the nearest number with exactly one digit after the decimal point (0.05 rounds up to 0.1).
样例输入
3
1000 50 1
10 10
100 100 4
10 10
10 90
90 10
90 90
3000 3000 4
1200 85
63 2500
2700 2650 
2990 100
样例输出
The safest point is (1000.0, 50.0).
The safest point is (50.0, 50.0).
The safest point is (1433.0, 1669.8).*/ 

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int X = 0, Y = 0, M = 0;
struct point {
	double x;
	double y;
}p[1050];

double dis(point p1, point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
double mindis(point p1) {//离最近点的距离
	double m = 20000;
	for (int i = 0; i < M; ++i) {
		if (dis(p1, p[i]) < m) {
			m = dis(p1, p[i]);
		}
	}
	return m;
}
int main() {
	int T = 0;
	cin >> T;
	point cur;
	point nxt;
	while (T--) {
		cin >> X >> Y >> M;
		for (int i = 0; i < M; ++i) {
			cin >> p[i].x >> p[i].y;
		}
		cur = p[0];
		for (double i = max(X,Y); i > 1e-8; i *= 0.98) {
			for (int j = -1; j <= 1; ++j) {
				for (int k = -1; k <= 1; ++k) {
					nxt.x = cur.x+i * j;
					nxt.y = cur.y+i * k;
					if (nxt.x > X || nxt.y > Y||nxt.x<0||nxt.y<0)
						continue;
					if (mindis(nxt)>mindis(cur)) {
						cur = nxt;
					}
				}
			}
		}
		cout <<fixed<<setprecision(1)<< "The safest point is (" << cur.x << ", " << cur.y << ")." << endl;

	}
	return 0;
}
