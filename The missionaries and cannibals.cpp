/*����
The missionaries and cannibals problem is usually stated as follows: 
Three missionaries and three cannibals are on one side of a river, along with a boat that can hold one or two people. 
Find a way to get everyone to the other side, without ever leaving a group of missionaries in one place (including the boat) outnumbered by the cannibals in that place.
Now the problem has been extended to be more complicated. There are m missionaries and m cannibals who want to cross the river. 
And the boat is also enlarged to be capable of supporting n people. 
In order to make all of them cross the river safely what is the least number of steps? 
Notice that when the boat goes across the river there must be at least one missionary or cannibal on the boat.

����
The input consists of only one line, and is made of two positive number m and n, where m �� 1000 and n �� 100.
���
Output the least number of steps needed. If the problem can't be solved, print -1 as the result.
��������
3 2
�������
11*/ 
#include<iostream>
#include<queue>
#include<set>
using namespace std;

struct states {
	int mis;//�󰶴���ʿ����
	int can;//��ʳ��������
	bool f;//�������Ϊtrue �����ұ�Ϊfalse
	int step;//ĿǰΪֹ���˶��ٲ� 
	int eval;//�������� Խ��Խ��
	bool operator <(const states& a)const {
		return eval < a.eval;
	}
	bool operator==(const states& a)const {
		return(mis == a.mis) && (can == a.can) && (f == a.f);
	}
};
struct cmp {
	bool operator()(const states& a, const states& b)const {
		if (a.mis != b.mis)
			return a.mis > b.mis;
		if (a.can != b.can)
			return a.can > b.can;
		
			return a.f > b.f;
		
	}
};
int m = 0, n = 0;
int ans = -1;
priority_queue<states>q;
set<states,cmp>ss;
bool check(states s) {
	if (s.mis < 0 || s.can < 0)
		return false;
	if (m - s.mis < 0 || m - s.can < 0)
		return false;
	if (s.mis != 0 && s.mis < s.can)
		return false;
	if (m - s.mis != 0 && m - s.mis < m - s.can)
		return false;
	return true;
}
bool is_successful(states s) {
	if (s.mis == 0 && s.can == 0)
		return true;
	return false;
}
void bfs() {
	while (!q.empty()) {
		states s = q.top();
		q.pop();
		for (int cc = 0; cc <= n; ++cc) {//ʳ�������� 
			states tmp;
			for (int mm = cc; mm + cc <= n; ++mm) {//����ʿ���� ����ʿ������ʳ�������� 
				if (cc == 0 && mm == 0)
					continue;
				if (s.f) {	//�������	���󿪵���	
					tmp.mis = s.mis - mm;
					tmp.can = s.can - cc;
					tmp.f = false;
					tmp.step = s.step + 1;
					tmp.eval = -(tmp.mis + tmp.can) + (tmp.f == true);
					if (is_successful(tmp)) {
						ans = tmp.step;
						return;
					}
					if (check(tmp)) {
						if (ss.find(tmp) == ss.end()) {//�ý��û���ѹ�
							q.push(tmp);
							ss.insert(tmp);
						}
					}
				}
				if (!s.f) {//�����ұ� ���ҿ����� 
					tmp.mis = s.mis + mm;
					tmp.can = s.can + cc;
					tmp.f = true;
					tmp.step = s.step + 1;
					tmp.eval = -(tmp.mis + tmp.can) + (tmp.f == true);
					if (check(tmp)) {
						if (ss.find(tmp) == ss.end()) {//�ý��û���ѹ�
							q.push(tmp);
							ss.insert(tmp);
						}
					}
				}
			}
			//����ʿû�е����
			if (s.f && cc != 0) {//������� ʳ���廮����ȥ
				tmp.mis = s.mis;
				tmp.can = s.can - cc;
				tmp.f = false;
				tmp.step = s.step + 1;
				tmp.eval = -(tmp.mis + tmp.can) + (tmp.f == true);
				if (is_successful(tmp)) {
						ans = tmp.step;
						return;
					}
				if (check(tmp)) {
					if (ss.find(tmp) == ss.end()) {//�ý��û���ѹ�
						q.push(tmp);
						ss.insert(tmp);
					}
				}
			}
			if (!s.f && cc != 0) {//�����ұ�  ʳ���廮������ 
				tmp.mis = s.mis;
				tmp.can = s.can + cc;
				tmp.f = true;
				tmp.step = s.step + 1;
				tmp.eval = -(tmp.mis + tmp.can) + (tmp.f == true);
				if (check(tmp)) {
					if (ss.find(tmp) == ss.end()) {//�ý��û���ѹ�
						q.push(tmp);
						ss.insert(tmp);
					}
				}
			}
		}
	}
}
int main() {

	cin >> m >> n;
	states init;
	init.mis = m;
	init.can = m;
	init.f = true;
	init.step = 0;
	q.push(init);
	bfs();
	cout << ans << endl;
	return 0;
}
