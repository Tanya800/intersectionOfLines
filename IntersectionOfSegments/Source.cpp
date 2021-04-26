#include<iostream>
#include<vector>  

#include "point.h"
#include "segment.h"
#include"swap-line.h"
#include <ctime>

#include <Windows.h>

using namespace std;

void requestFromUsers(int numberUsers,int numberRequest) {

	do {
		int n;
		cout << "������� ���������� ��������: ";
		cin >> n;

		while (n < 1 || n > 100) {
			cout << "������� ���������� �������� �� 1 �� 100: ";
			cin >> n;
		}

		vector <Point> P;
		vector <Segment> Vec;

		for (int i = 0; i < n; i++) {

			double x1, x2, y1, y2;
			cout << "������� ���������� ������� " << i + 1 << "(x1,y1,x2,y2):" << endl;
			cin >> x1 >> y1 >> x2 >> y2;
			/*if (i < (n - 1)) {
				x1 = 0;
				x2 = i + 1;
				y1 = i + 1;
				y2 = 0;
			}
			else {
				x1 = 0;
				x2 = n/2+0.5;
				y1 = 0;
				y2 = n/2+0.5;
			}
			*/
			Point p1(x1, y1, 0), p2(x2, y2, 1);
			P.push_back(p1);
			P.push_back(p2);
			Vec.push_back(Segment(p1, p2));
		}

		Vec = sortSegm(Vec);
		cout << "��������� ������:" << endl;
		for (int i = 0; i < n; i++) {
			cout << "������� " << i << endl;
			print(Vec[i]);
			cout << endl;
		}

		double start_time, end_time;
		vector<Point> f;

		for (int i = 0; i < numberRequest; i++) {
			start_time = clock();
			f = findIntersectionPoints(P, Vec);
			end_time = clock(); // �������� �����
			Sleep(2000);
		}
		
		double  search_time = end_time - start_time; // ������� �����

		if (f.size() > 0) {
			cout << endl;
			for (int i = 0; i < f.size(); i++) {
				cout << i + 1 << " ����� ����������� (" << f[i].x << " ; " << f[i].y << ")" << endl;
			}
		}
		else cout << "����������� � ������ ������ �������� �� �������!" << endl;

		cout << "����� ���������� ���������: " << search_time << endl;

		numberUsers--;
	} while (numberUsers > 0);
	
}

int main() {
	setlocale(LC_ALL, "RUS");
	requestFromUsers(2, 5);
	return 0;
}

