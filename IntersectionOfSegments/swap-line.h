#pragma once
#include<vector>

#include"point.h"
#include"segment.h"
#include"intersection.h"


struct segmIntWithPoint
{
	Point I;
	Segment Below;
	Segment Above;
	segmIntWithPoint() {};
	segmIntWithPoint(Point I, Segment Below, Segment Above) : I(I), Above(Above), Below(Below) {};
};

vector <Segment> sortSegm(vector <Segment> S) {

	for (int i = 0; i < S.size() - 1; i++) {
		if (S[i] > S[i + 1]) {
			Segment temp = S[i];
			S[i] = S[i + 1];
			S[i + 1] = temp;
		}
	}
	return S;
}

//присутствует ли точка в векторе точке
bool findPoint(Point p, vector<Point> V) {
	for (int i = 0; i < V.size(); i++) {
		if (p == V[i])
			return true;
	}
	return false;
}

//вернуть отрезок по точке из вектора отрезков
Segment findSegmentofVector(Point E, vector<Segment> S) {
	for (int i = 0; i < S.size(); i++) {
		if (((S[i].p1.x == E.x &&S[i].p1.y == E.y) || (S[i].p2.x == E.x && S[i].p2.y == E.y)))
			return S[i];
	}
}

int findIndexofSegment(Segment s, vector<Segment> S) {
	int index = -1;
	for (int i = 0; i < S.size(); i++) {
		if (S[i] == s) index = i;
	}
	return index;
}

void ShakerSort(vector<Point>& values) {
	if (values.empty()) {
		return;
	}
	int left = 0;
	int right = values.size() - 1;
	while (left <= right) {
		for (int i = right; i > left; --i) {
			if (values[i - 1] > values[i]) {
				swap(values[i - 1], values[i]);
			}
		}
		++left;
		for (int i = left; i < right; ++i) {
			if (values[i] > values[i + 1]) {
				swap(values[i], values[i + 1]);
			}
		}
		--right;
	}
}



Point findIntersection(Segment S1, Segment S2) {
	double x = NAN, y = NAN;
	Point I(x, y, 2);
	if (intersect(S1.p1.x, S1.p2.x, S2.p1.x, S2.p2.x, S1.p1.y, S1.p2.y, S2.p1.y, S2.p2.y, x, y)) {
		if (pointOnSeg(S1.p1, S2.p2, Point(x, y, 2)))
			I = Point(x, y, 2);
	}
	return I;

}

vector<Point> findIntersectionPoints(vector<Point> P, vector <Segment> Vec) {
	vector <Segment> SL;
	vector<Point> IL;
	vector<Point> EQ = P;
	ShakerSort(EQ);
	vector <segmIntWithPoint> allIntSeg;
	
	while (!EQ.empty())
	{
		Point E = EQ.front();
		if (E.e == 0) {//left endpoint
			Segment segE = findSegmentofVector(E, Vec);
			SL.push_back(segE);
			int nextSeg = findIndexofSegment(segE, SL);
			Point I;
			if (nextSeg + 1 < SL.size()) {
				Segment segA = SL[nextSeg + 1];
				I = findIntersection(segE, segA);

				if (isNotNAN(I)) {
					EQ.push_back(I);
					allIntSeg.push_back(segmIntWithPoint(I, segE, segA));
				}
			}

			if (nextSeg - 1 >= 0) {
				Segment segB = SL[nextSeg - 1];
				I = findIntersection(segE, segB);
				if (isNotNAN(I)) {
					EQ.push_back(I);
					allIntSeg.push_back(segmIntWithPoint(I, segB, segE));
				}
			}
		}
		else if (E.e == 1) {//right endpoint
			Segment segE = findSegmentofVector(E, Vec);
			int nextSeg = findIndexofSegment(segE, SL);
			if (nextSeg + 1 < SL.size() && nextSeg - 1 >= 0) {
				Segment segA = SL[nextSeg + 1];
				Segment segB = SL[nextSeg - 1];
				Point I = findIntersection(segA, segB);
				if (isNotNAN(I)) {
					if (!findPoint(I, EQ)) {
						EQ.push_back(I);
						allIntSeg.push_back(segmIntWithPoint(I, segB, segA));
					}
				}
			}
			SL.erase(SL.begin() + nextSeg);
		}
		else {// E is an intersection event
			IL.push_back(E);
			Segment sE1, sE2;
			for (int i = 0; i < allIntSeg.size(); i++) {
				if (allIntSeg[i].I == E) {
					sE1 = allIntSeg[i].Below;
					sE2 = allIntSeg[i].Above;
				}
			}
			int indexBelow = findIndexofSegment(sE1, SL);
			int indexAbove = findIndexofSegment(sE2, SL);

			if (indexAbove != -1 && indexBelow != -1) {

				Segment temp = SL[indexAbove];
				SL[indexAbove] = SL[indexBelow];
				SL[indexBelow] = temp;

				if ((indexBelow - 1) >= 0) {
					Segment segA = SL[indexBelow - 1];
					Point I = findIntersection(SL[indexBelow], segA);
					if (isNotNAN(I)) {
						if (!findPoint(I, EQ))
						{
							EQ.push_back(I);
							allIntSeg.push_back(segmIntWithPoint(I, segA, SL[indexBelow]));
						}

					}
				}
				if ((indexAbove + 1) < SL.size()) {
					Segment segB = SL[indexAbove + 1];
					Point I = findIntersection(SL[indexAbove], segB);
					if (isNotNAN(I)) {
						if (!findPoint(I, EQ)) {
							EQ.push_back(I);
							allIntSeg.push_back(segmIntWithPoint(I,SL[indexAbove],segB));
						}

					}
				}

			}

		}
		EQ.erase(EQ.begin());
		ShakerSort(EQ);
	}
	allIntSeg.clear();
	return IL;
}
