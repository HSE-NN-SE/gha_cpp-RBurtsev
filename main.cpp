#include <iostream>
#include <math.h>
#include<fstream>
#include<vector>
#include<cmath>

using namespace std;

class Point {
private:
	int ID;//ID point
	int x, y;//coordinate
	int nextID;//ID point after that
	int b;//buzy
public:
	int getID() {
		return ID;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getB() {
		return b;
	}
	int getnextID() {
		return nextID;
	}
	Point() {
		x = 0;
		y = 0;
		ID = 0;
		nextID = 0;
		b = 0;
	}
	Point(int ID, int x, int y, int nextID) {
		this->ID = ID;
		this->x = x;
		this->y = y;
		this->nextID = nextID;
		this->b = b;
	}
	Point(const Point& P) {
		this->ID = P.ID;
		this->x = P.x;
		this->y = P.y;
		this->nextID = P.nextID;
		this->b = P.b;
	}
	Point(int ID, int x, int y) {
		this->ID = ID;
		this->x = x;
		this->y = y;
		nextID = 0;
	}
	void setID(int ID) {
		this->ID = ID;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setNextID(int k) {
		this->nextID = k;
	}
	void setB(int b) {
		this->b = b;
	}
	double distance(const Point P) {//count distance
		return abs(sqrt(((static_cast<double>(P.x) - static_cast<double>(x)) * (static_cast<double>(P.x) - static_cast<double>(x))) + (static_cast<double>(P.y) - static_cast<double>(y)) * (static_cast<double>(P.y) - static_cast<double>(y))));
	}

};

void check1(vector<vector<int>>& space, int n, int start) {
	int next = start;
	int last = 0;
	int k = 0;
	int i = 0;
	cout << next << ' ';
	while (i < n) {
		for (int j = 0; j < 2; j++) {
			if (space[next][j] != last) {
				cout << space[next][j] << ' ';
				last = next;
				next = space[next][j];
				break;
			}
		}
		i++;
	}
	cout << endl;
}

bool check(vector<vector<int>>& space, int n, int start, int end) {
	vector<int>used(n + 1, 0);
	int next = start;
	used[next] = 1;
	int i = 0;
	while (i < n) {
		int k = 0, j = 0, l = 0;
		while (j < 2) {
			if (!used[space[next][j]]) {
				used[next] = 1;
				next = space[next][j];
				k = 1;
				break;
			}
			j++;
		}
		if (next == end) {
			i = n;
			break;
		}
		i++;
		if (i == n)
			break;
		if (k == 0)
			break;
	}
	if (i == n)
		return 1;
	else
		return 0;
}

double path(vector<Point>& space, int n) {
	double ans = 0;
	for (int i = 1; i < n; i++) {
		ans += space[i].distance(space[i + 1]);
	}
	ans += space[n].distance(space[1]);
	return ans;
}

double checkpath(vector<vector<int>>& space, vector<Point>& spaceid, int v1start, int v1end, int v2start, int v2end, double minpath) {
	double v1 = spaceid[v1start].distance(spaceid[space[v1start][v1end]]);
	double v2 = spaceid[v2start].distance(spaceid[space[v2start][v2end]]);
	double n1 = spaceid[v1start].distance(spaceid[space[v2start][v2end]]);
	double n2 = spaceid[v2start].distance(spaceid[space[v1start][v1end]]);
	return minpath - v1 - v2 + n1 + n2;
}

int main() {
	ofstream outf;
	int n = 0, ID, x, y, nextID;
	char* str = new char[1024];
	ifstream base("inf.txt");
	while (!base.eof())
	{
		base.getline(str, 1024, '\n');
		n++;
	}
	base.close();
	delete str;
	base.open("inf.txt");
	vector<Point>space(n + 1);
	int startid = 1;
	for (int i = 1; i < n + 1; i++) {
		base >> ID;
		base >> x;
		base >> y;
		space[i].setID(ID);
		space[i].setX(x);
		space[i].setY(y);
		space[i].setB(0);
	}
	int h = 0;
	double minpath = path(space, n);
	cout << minpath << endl;
	vector<vector<int>>used(n + 1, vector<int>(n + 1, 0));
	while (true) {
		int num = 0, l1, l2;
		double s1, s2;
		double d1, d2, minpath1 = minpath;
		for (int i = 1; i < n + 1; i++) {
			for (int j = 1; j < n + 1; j++) {
				if (i != j) {
					d1 = 0;
					d2 = 0;
					Point n1 = space[i];
					Point n2 = space[j];
					if (i == 1)
						d1 += space[i].distance(space[n]);
					else
						d1 += space[i].distance(space[i - 1]);
					if (j == 1)
						d1 += space[j].distance(space[n]);
					else
						d1 += space[j].distance(space[j - 1]);
					if (i == n)
						d1 += space[i].distance(space[1]);
					else
						d1 += space[i].distance(space[i + 1]);
					if (j == n)
						d1 += space[j].distance(space[1]);
					else
						d1 += space[j].distance(space[j + 1]);

					space[i] = n2;
					space[j] = n1;
					if (i == 1)
						d2 += space[i].distance(space[n]);
					else
						d2 += space[i].distance(space[i - 1]);
					if (j == 1)
						d2 += space[j].distance(space[n]);
					else
						d2 += space[j].distance(space[j - 1]);
					if (i == n)
						d2 += space[i].distance(space[1]);
					else
						d2 += space[i].distance(space[i + 1]);
					if (j == n)
						d2 += space[j].distance(space[1]);
					else
						d2 += space[j].distance(space[j + 1]);

					if (minpath1 > minpath - d1 + d2) {
						s1 = d1;
						s2 = d2;
						minpath1 = minpath - d1 + d2;
						l1 = i;
						l2 = j;
						num = 1;
					}
					space[i] = n1;
					space[j] = n2;
				}
			}
		}
		if (num == 1) {
			Point n1 = space[l1];
			Point n2 = space[l2];
			space[l1] = n2;
			space[l2] = n1;
			minpath = minpath1;
			cout << minpath << endl;
			/*cout <<check(space,n,startid)<<' '<< space[v2start][v2end] << ' ' << space[v1start][v1end] << endl;*/
		}
		else {
			break;
		}
	}
	outf.open("path.txt");

	for (int i = 1; i < n + 1; i++) {
		outf << space[i].getID() << ' ' << space[i].getX() << " " << space[i].getY() << endl;
	}

	system("pause");
	return 0;
}
