/*描述
Luke wants to upgrade his home computer network from 10mbs to 100mbs. 
His existing network uses 10base2 (coaxial) cables that allow you to connect any number of computers together in a linear arrangement.
Luke is particulary proud that he solved a nasty NP-complete problem in order to minimize the total cable length.
Unfortunately, Luke cannot use his existing cabling. 
The 100mbs system uses 100baseT (twisted pair) cables. 
Each 100baseT cable connects only two devices: either two network cards or a network card and a hub. 
(A hub is an electronic device that interconnects several cables.) 
Luke has a choice: He can buy 2N-2 network cards and connect his N computers together by inserting one or more cards into each computer and connecting them all together.
Or he can buy N network cards and a hub and connect each of his N computers to the hub. 
The first approach would require that Luke configure his operating system to forward network traffic.
However, with the installation of Winux 2007.2, Luke discovered that network forwarding no longer worked. 
He couldn't figure out how to re-enable forwarding, and he had never heard of Prim or Kruskal, so he settled on the second approach: N network cards and a hub.

Luke lives in a loft and so is prepared to run the cables and place the hub anywhere. 
But he won't move his computers. He wants to minimize the total length of cable he must buy.
输入
The first line of input contains a positive integer N <= 100, the number of computers.
N lines follow; each gives the (x,y) coordinates (in mm.) of a computer within the room. All coordinates are integers between 0 and 10,000.
输出
Output consists of one number, the total length of the cable segments, rounded to the nearest mm.
样例输入
4
0 0
0 10000
10000 10000
10000 0
样例输出
28284*/

#include<iostream>
#include<cmath>
using namespace std;
int N = 0;//计算机的数量
struct point {
	double x;
	double y;
};
point cpt[110];//computer的坐标 
double distance(point p1, point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double sumdis(point p1) {
	double sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += distance(cpt[i], p1);
	}
	return sum;
}
void input() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> cpt[i].x >> cpt[i].y;
	}
	return;
}
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
double ans = 0;
void climb() {//爬山算法
	double step = 5000;
	point p;
	p.x = 5000;
	p.y = 5000;
	double sum = sumdis(p);
	point tmp;
	point next = p;;
	while (step > 0.1) {
		for (int i = 0; i < 4; ++i) {//四个方向
			tmp.x = p.x + dx[i] * step;
			tmp.y = p.y + dy[i] * step;
			if (tmp.x > 10000 || tmp.y > 10000 || tmp.x < 0 || tmp.y < 0)
				continue;
			if (sumdis(tmp) < sum) {
				p = tmp;//距离和更小 选为下一步要走的点
				sum = sumdis(tmp);
			}
		}
		step /= 2;
	}
	ans = sum;
}
int main() {
	input();
	climb();
	if (ans - (int)ans >= 0.5)
		ans += 1;
	cout << (int)ans << endl;
	return 0;
}
