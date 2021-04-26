#pragma once
#include<iostream>

using namespace std;

bool areCollinear(double x1, double y1, double x2, double y2) {
	return x1 / x2 == y1 / y2 ? true : false;// �������� �� ��������������
}

double getMin(double x1, double x2) {
	return x1 < x2 ? x1 : x2;
}

double getMax(double x1, double x2) {
	return x1 > x2 ? x1 : x2;
}

// �������� �� ����������� �������� �� ���, ����������� ���������� ��������� ������������ ������ ��������
bool projectionsIntersect(double x1, double x2, double x3, double x4) {
	return ((getMin(x1, x2) <= getMin(x3, x4) && getMin(x3, x4) <= getMax(x1, x2)) || ((getMin(x3, x4) <= getMin(x1, x2) && getMin(x1, x2) <= getMax(x3, x4))));
}

// ���������� ������������ ���� ������� ��������� ������
double getSlope(double x1, double  y1, double x2, double y2) {
	return (y2 - y1) / (x2 - x1);
}

// ���������� ���������� ����� ��������� ������
double getYIntercept(double x1, double  y1, double x2, double y2) {
	return (x2 * y1 - x1 * y2) / (x2 - x1);
}

// ���������� �������� ���� ����� ���������
double getCos(double x1, double  y1, double x2, double y2) {
	return (x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) + sqrt(x2 * x2 + y2 * y2));
}

bool intersect(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4, double& intX, double& intY) {
	bool intersec = 0;
	double slope1, slope2; // ������������ ����� ������� ��������� ������, �� ������� ����������� �������
	bool f1 = false, f2 = false; // ���������� ����� ��� ������ ���� x = a 
	double yIntercept1, yIntercept2; // ��������� ����� ��������� ������, �� ������� ����������� �������
	double xIntersection, yIntersection; // ���������� ����� �����������, ���� ��� ����������
	double vx1 = x2 - x1;
	double vy1 = y2 - y1; // �������� ���������� ��������,
	double vx2 = x4 - x3; // ���������� ������� ���������
	double vy2 = y4 - y3;
	slope1 = (vx1 != 0 ? getSlope(x1, y1, x2, y2) : 0); // ��� ������ ���� x = a
	slope2 = (vx2 != 0 ? getSlope(x3, y3, x4, y4) : 0); // ����������� �������� 0 ������������ ���� �������
	vx1 != 0 ? yIntercept1 = getYIntercept(x1, y1, x2, y2) : f1 = true; // ��� ������ ���� x = a 
	vx2 != 0 ? yIntercept2 = getYIntercept(x3, y3, x4, y4) : f2 = true; // ����������� ����� �������� true
	if (!f1 && !f2) {
		xIntersection = (yIntercept2 - yIntercept1) / (slope1 - slope2); // ������� ������� ������� ��������� 
		yIntersection = slope1 * xIntersection + yIntercept1;
		if (getCos(x1 - xIntersection, y1 - yIntersection, x2 - xIntersection, y2 - yIntersection) <= 0 && getCos(x3 - xIntersection, y3 - yIntersection, x4 - xIntersection, y4 - yIntersection) <= 0) // ��������� ��������� �� ����� �� ����� �������� 
			intersec = 1;
		else if (yIntercept1 == yIntercept2) {
			if (projectionsIntersect(x1, x2, x3, x4))
				intersec = 0;
			else
				intersec = 0;
		}
		else if (yIntercept1 != yIntercept2 && (areCollinear(vx1, vy1, vx2, vy2) || (y1 == y2 && y3 == y4)))
			intersec = 0;
		else
			intersec = 0;
	} // ���� ���������� ������������ ��� ���� ��������, ����� ���, ��� ���� �� ���� �� ��� ���������� �� ������ ���� x = a
	else {
		if (slope1 == 0 && slope2 == 0 && f1 && f2) {
			if (x1 == x4 && projectionsIntersect(y1, y2, y3, y4))
				intersec = 0;
			else if (x1 != x4)
				intersec = 0;
			else
				intersec = 0;
		} // ���� ��� ���� ������ ���� x = a
		else if (f1 ^ f2 && slope1 == 0 && slope2 == 0) {
			if (f1) {
				swap(x1, x3);
				swap(x2, x4);
				swap(y1, y3);
				swap(y2, y4);
				swap(yIntercept1, yIntercept2);
			}
			yIntersection = y1;
			xIntersection = x3;
			if (getCos(x1 - xIntersection, y1 - yIntersection, x2 - xIntersection, y2 - yIntersection) <= 0 && getCos(x3 - xIntersection, y3 - yIntersection, x4 - xIntersection, y4 - yIntersection) <= 0)
				intersec = 1;
			else
				intersec = 0;
		} // ���� ��� ������ ���� y = b � x = a
		else if (slope1 == 0 ^ slope2 == 0) {
			if (slope1 == 0) {
				swap(x1, x3);
				swap(x2, x4);
				swap(y1, y3);
				swap(y2, y4);
				swap(yIntercept1, yIntercept2);
			}
			xIntersection = x3;
			yIntersection = x3 + yIntercept1;
			if (getCos(x1 - xIntersection, y1 - yIntersection, x2 - xIntersection, y2 - yIntersection) <= 0 && getCos(x3 - xIntersection, y3 - yIntersection, x4 - xIntersection, y4 - yIntersection) <= 0)
				intersec = 1;
			else
				intersec = 0;
		} // ���� ���������� ������������, ����� ������ ���� ����� ����� ��� x = a, � ������ y = kx +b
	} // ���� ���������� ������������, ���� ���� �� ���� ������� ��������� �� ������ ���� x = a
	if (intersec) {
		intX = xIntersection;
		intY = yIntersection;
		return true;
	}
	else return false;
}
