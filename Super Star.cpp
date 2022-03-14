/*
描述
During a voyage of the starship Hakodate-maru , researchers found strange synchronized movements of stars. Having heard these observations, Dr. Extreme proposed a theory of "super stars". Do not take this term as a description of actors or singers. It is a revolutionary theory in astronomy. According to this theory, starts we are observing are not independent objects, but only small portions of larger objects called super stars. A super star is filled with invisible (or transparent) material, and only a number of points inside or on its surface shine. These points are observed as stars by us. In order to verify this theory, Dr. Extreme wants to build motion equations of super stars and to compare the solutions of these equations with observed movements of stars. As the first step, he assumes that a super star is sphere-shaped, and has the smallest possible radius such that the sphere contains all given stars in or on it. This assumption makes it possible to estimate the volume of a super star, and thus its mass (the density of the invisible material is known). You are asked to help Dr. Extreme by writing a program which, given the locations of a number of stars, finds the smallest sphere containing all of them in or on it. In this computation, you should ignore the sizes of stars. In other words, a star should be regarded as a point. You may assume the universe is a Euclidean space.

输入
The input consists of multiple data sets. Each data set is given in the following format.

n
x1 y1 z1
x2 y2 z2
. . .
xn yn zn

The first line of a data set contains an integer n, which is the number of points. It satisfies the condition 4 <= n <= 30.

The location of n points are given by three-dimensional orthogonal coordinates: (xi, yi, zi) (i = 1, ..., n). Three coordinates of a point appear in a line, separated by a space character. Each value is given by a decimal fraction, and is between 0.0 and 100.0 (both ends inclusive). Points are at least 0.01 distant from each other.

The end of the input is indicated by a line containing a zero.
输出
For each data set, the radius of the smallest sphere containing all given points should be printed, each in a separate line. The printed values should have 5 digits after the decimal point. They may not have an error greater than 0.00001.
样例输入
4
10.00000 10.00000 10.00000
20.00000 10.00000 10.00000
20.00000 20.00000 10.00000
10.00000 20.00000 10.00000
4
10.00000 10.00000 10.00000
10.00000 50.00000 50.00000
50.00000 10.00000 50.00000
50.00000 50.00000 10.00000
0
样例输出
7.07107
34.64102*/

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int n = 0;
struct star {
	double x;
	double y;
	double z;
}s[40];
double dis(star s1, star s2) {
	return sqrt((s1.x - s2.x) * (s1.x - s2.x) + (s1.y- s2.y) * (s1.y - s2.y) + (s1.z - s2.z) * (s1.z - s2.z));
}
double maxdis(star s1) {//s1距离所有点中最大的距离
	double m = 0;
	for (int i = 0; i < n; ++i) {
		if (dis(s1, s[i]) > m) {
			m = dis(s1, s[i]);
		}
	}
	return m;
}
int main() {
	while (cin >> n) {
		if (n == 0)
			break;
		double x_sum = 0, y_sum =0, z_sum = 0;
		for (int i = 0; i < n; ++i) {
			cin >> s[i].x >> s[i].y >> s[i].z;
		}
		star cur=s[0];
		double ans = 300;
		for (double step = 100; step > 1e-10; step *= 0.99) {
			int k = 0;
			for (int i = 0; i < n; ++i) {
				if (dis(cur, s[i]) > dis(cur, s[k])) {
					k = i;
				}
			}
			double d = dis(cur, s[k]);
			if (d < ans)
				ans = d;
			cur.x += step * (s[k].x - cur.x) / d;
			cur.y += step * (s[k].y - cur.y) / d;
			cur.z += step * (s[k].z - cur.z) / d;
		}
		cout <<fixed<<setprecision(5)<< ans << endl;
	}
	return 0;
} 
