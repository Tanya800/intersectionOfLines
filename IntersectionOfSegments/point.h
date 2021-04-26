#pragma once

struct Point {
	double x, y;
	int e = 0;// left ==0 ; right == 1
	Point() {};
	Point(double x, double y, int e) : x(x), y(y), e(e) {};
};


//сравнение точек
bool operator==(Point p1, Point p2) {
	if (p1.x == p2.x && p1.y == p2.y) return true;
	else return false;
}
bool operator>(Point p1, Point p2) {
	if (p1.x > p2.x) return true;
	else if (p1.x == p2.x && p1.y > p2.y) return true;
	else return false;
}


Point min(Point p1, Point p2) {
	if (p2.x > p1.x) return p1;
	else return p2;

}

Point max(Point p1, Point p2) {
	if (p2.x > p1.x) return p2;
	else return p1;

}

bool pointOnSeg(Point p1, Point p2, Point pp) {
	Point minX = min(p1, p2),
		maxX = max(p1, p2);
	int answer = 1;
	answer *= (pp.x > minX.x) ? 1 : 0;
	answer *= (maxX.x > pp.x) ? 1 : 0;
	return answer;
}


bool isNotNAN(Point I) {
	if (I.x != NAN && I.x == I.x) return true;
	else return false;
}