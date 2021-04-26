#pragma once
#include<iostream>
struct Segment
{
	Point p1, p2;
	Segment() {};
	Segment(Point p1, Point p2) : p1(p1), p2(p2) {}; 
};

//сравнение отрезков
bool operator==(Segment S1, Segment S2) {
	if ((S1.p1 == S2.p1) && (S1.p2 == S2.p2)) return true;
	else return false;
}
bool operator>(Segment S1, Segment S2) {
	if ((S1.p1 > S2.p1)) return true;
	else return false;
}


void print(Segment S) {
	std::cout << "( " << S.p1.x << "; " << S.p1.y << ")"
		<< "( " << S.p2.x << "; " << S.p2.y << ")";
}

//получить вектор отрезков из вектора точек
std::vector<Segment> vectorFromProints(std::vector<Point> P) {
	std::vector <Segment> S;
	for (int i = 0; i < P.size() - 1; i += 2) {
		S.push_back(Segment(P[i], P[i + 1]));
	}
	return S;
}