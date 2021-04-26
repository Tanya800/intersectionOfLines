#pragma once
#include<iostream>

using namespace std;

bool areCollinear(double x1, double y1, double x2, double y2) {
	return x1 / x2 == y1 / y2 ? true : false;// проверка на коллинеарность
}

double getMin(double x1, double x2) {
	return x1 < x2 ? x1 : x2;
}

double getMax(double x1, double x2) {
	return x1 > x2 ? x1 : x2;
}

// Проверка на пересечение проекций на оси, посредством нахождения взаимного расположения концов проекций
bool projectionsIntersect(double x1, double x2, double x3, double x4) {
	return ((getMin(x1, x2) <= getMin(x3, x4) && getMin(x3, x4) <= getMax(x1, x2)) || ((getMin(x3, x4) <= getMin(x1, x2) && getMin(x1, x2) <= getMax(x3, x4))));
}

// Вычисление коэффициента угла наклона уравнения прямой
double getSlope(double x1, double  y1, double x2, double y2) {
	return (y2 - y1) / (x2 - x1);
}

// Вычисление свободного члена уравнения прямой
double getYIntercept(double x1, double  y1, double x2, double y2) {
	return (x2 * y1 - x1 * y2) / (x2 - x1);
}

// Нахождение косинуса угла между векторами
double getCos(double x1, double  y1, double x2, double y2) {
	return (x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) + sqrt(x2 * x2 + y2 * y2));
}

bool intersect(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4, double& intX, double& intY) {
	bool intersec = 0;
	double slope1, slope2; // Коэффициенты углов наклона уравнений прямых, на которых расположены отрезки
	bool f1 = false, f2 = false; // Логические флаги для прямых вида x = a 
	double yIntercept1, yIntercept2; // Свободные члены уравнений прямых, на которых расположены отрезки
	double xIntersection, yIntersection; // Координаты точки пересечения, если она существует
	double vx1 = x2 - x1;
	double vy1 = y2 - y1; // Вычислим координаты векторов,
	double vx2 = x4 - x3; // Задаваемых данными отрезками
	double vy2 = y4 - y3;
	slope1 = (vx1 != 0 ? getSlope(x1, y1, x2, y2) : 0); // Для прямых вида x = a
	slope2 = (vx2 != 0 ? getSlope(x3, y3, x4, y4) : 0); // Присваиваем значение 0 коэффициенту угла наклона
	vx1 != 0 ? yIntercept1 = getYIntercept(x1, y1, x2, y2) : f1 = true; // Для прямых вида x = a 
	vx2 != 0 ? yIntercept2 = getYIntercept(x3, y3, x4, y4) : f2 = true; // Присваиваем флагу значение true
	if (!f1 && !f2) {
		xIntersection = (yIntercept2 - yIntercept1) / (slope1 - slope2); // Находим решение системы уравнений 
		yIntersection = slope1 * xIntersection + yIntercept1;
		if (getCos(x1 - xIntersection, y1 - yIntersection, x2 - xIntersection, y2 - yIntersection) <= 0 && getCos(x3 - xIntersection, y3 - yIntersection, x4 - xIntersection, y4 - yIntersection) <= 0) // Проверяем находится ли точка на обоих отрезках 
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
	} // Блок нахождения расположения для всех отрезков, кроме тех, где хотя бы один из них расположен на прямой вида x = a
	else {
		if (slope1 == 0 && slope2 == 0 && f1 && f2) {
			if (x1 == x4 && projectionsIntersect(y1, y2, y3, y4))
				intersec = 0;
			else if (x1 != x4)
				intersec = 0;
			else
				intersec = 0;
		} // Блок для двух прямых вида x = a
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
		} // Блок для прямых вида y = b и x = a
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
		} // Блок нахождения расположения, когда только одна пряма имеет вид x = a, а вторая y = kx +b
	} // Блок нахождения расположения, если хотя бы один отрезок находится на прямой вида x = a
	if (intersec) {
		intX = xIntersection;
		intY = yIntersection;
		return true;
	}
	else return false;
}
