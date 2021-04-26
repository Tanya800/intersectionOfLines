#include "pch.h"
#include "CppUnitTest.h"
#include"../IntersectionOfSegments/swap-line.h"
#include"../IntersectionOfSegments/intersection.h"
#include"../IntersectionOfSegments/point.h"
#include"../IntersectionOfSegments/segment.h"
#include<vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace inersectionSegmentsTests
{
	TEST_CLASS(inersectionSegmentsTests)
	{
	public:
		
		TEST_METHOD(nullIntersectPoint)
		{
			vector<Point> P;
			vector<Segment> S;
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size()==0);
		}

		TEST_METHOD(onePoint)
		{
			vector<Point> P = { Point(0,0,0) };
			vector<Segment> S;
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size() == 0);
		}

		TEST_METHOD(oneSegment)
		{
			vector<Point> P = { Point(0,0,0),Point(1,1,1) };
			vector<Segment> S = vectorFromProints(P);
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size() == 0);
		}

		TEST_METHOD(notIntersectPoint)
		{
			vector<Point> P = { Point(1,3,0), Point(3,4,1),
								Point(2,1,0), Point(3,3,1)};
			
			vector<Segment> S = vectorFromProints(P);
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size() == 0);
		}


		TEST_METHOD(oneIntersectPoint)
		{
			Point p1(0,0,0), p2(1,1,1), p3(0,1,0), p4(1,0,1);
			vector<Point> P = { p1,p2,p3,p4 };
			vector<Segment> S = vectorFromProints(P);
			vector<Point> interSPoint = findIntersectionPoints(P,S);
			Point ExpectPoint(0.5,0.5,2) ;
			Assert::IsTrue(interSPoint.size() == 1);
			Assert::AreEqual(interSPoint.at(0).x, ExpectPoint.x);
			Assert::AreEqual(interSPoint.at(0).y, ExpectPoint.y);
		}

		TEST_METHOD(twoIntersectPoint)
		{
			Point p1(0, 0, 0), p2(10, 10, 1),
				p3(0, 2, 0), p4(2, 0, 1),
				p5(0, 4, 0), p6(4, 0, 1);
			vector<Point> P = { p1,p2,p3,p4,p5,p6 };
			vector<Segment> S = vectorFromProints(P);
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size() == 2);
		}

		TEST_METHOD(threeIntersectPoint)
		{
			Point p1(0, 0, 0), p2(6, 6, 1),
				p3(0, 2, 0), p4(2, 0, 1),
				p5(0, 4, 0), p6(4, 0, 1),
				p7(0, 6, 0), p8(6, 0, 1);
			vector<Point> P = { p1,p2,p3,p4,p5,p6,p7,p8 };
			vector<Segment> S = vectorFromProints(P);
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size() == 3);
			
		}

		TEST_METHOD(fourIntersectPoint)
		{
			Point p1(0.245, 0.147, 0.333), p2(6.21, 6.254, 1.03),
				p3(0.02, 2.02, 0.54), p4(2.215, 0.125, 1.215),
				p5(0.21, 4.15, 0.1), p6(4.2, 0.2, 1.2),
				p7(0.4, 6.5, 0.78), p8(6.47, 0.5, 1.368);
			vector<Point> P = { p1,p2,p3,p4,p5,p6,p7,p8 };
			vector<Segment> S = vectorFromProints(P);
			vector<Point> interSPoint = findIntersectionPoints(P, S);
			Assert::IsTrue(interSPoint.size() == 3);

		}
	};
}

namespace interPoints
{
	TEST_CLASS(interPoints)
	{
	public:

		TEST_METHOD(rightInterPoint)
		{
			double x1=3,  x2=1,  x3=1,  x4=2,
				y1=3,  y2=1,  y3=1,  y4=3,
				intX=0,  intY=0;
			bool answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsTrue(answer);

		}

		TEST_METHOD(parallelLines)
		{
			double x1 = 1,
				   x2 = 1,
				   x3 = 2,
				   x4 = 2,
				   y1 = 2, 
				   y2 = 5,
				   y3 = 2, 
				   y4 = 5, 
				   intX = 0,
				   intY = 0;
			bool answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsFalse(answer);
		}

		TEST_METHOD(oneTypesofLines)
		{
			double x1 = 0,
				x2 = 2,
				y1 = 1,
				y2 = 5,

				x3 = 3,
				x4 = 4,
				y3 = 7,
				y4 = 9,

				intX = 0,
				intY = 0;

			bool answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsFalse(answer);
			{   x1 = 0,
				x2 = 2,
				y1 = 0,
				y2 = 2,

				x3 = 3,
				x4 = 5,
				y3 = 3,
				y4 = 5,

				intX = 0,
				intY = 0;
			}
			answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsFalse(answer);

		}

		TEST_METHOD(twoTypesofLines)
		{
			double x1 = 0,
				x2 = 5,
				x3 = 0,
				x4 = 4,
				y1 = 5,
				y2 = 5,
				y3 = 0,
				y4 = 4,
				intX = 0,
				intY = 0;
			bool answerFasle = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			bool answerTrue = intersect(x1, x2, x3, 5, y1, y2, y3, 5, intX, intY);
			Assert::IsTrue(answerTrue);
			Assert::IsFalse(answerFasle);
		}

		TEST_METHOD(perpendicularLines)
		{
			double x1 = 1,
				x2 = 5,
				y1 = 5,
				y2 = 5,

				x3 = 3,
				x4 = 3,
				y3 = 3,
				y4 = 8,

				intX = 0,
				intY = 0;

			bool answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsTrue(answer);
		}

		TEST_METHOD(collinearLines)
		{
			double x1 = 0,
				x2 = 5,
				y1 = 0,
				y2 = 5,

				x3 = 2,
				x4 = 3,
				y3 = 2,
				y4 = 3,

				intX = 0,
				intY = 0;

			bool answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsFalse(answer);

			{
				x1 = 0,
				x2 = 5,
				y1 = 0,
				y2 = 5,

				x3 = 5,
				x4 = 6,
				y3 = 5,
				y4 = 6,

				intX = 0,
				intY = 0;
			}
			answer = intersect(x1, x2, x3, x4, y1, y2, y3, y4, intX, intY);
			Assert::IsFalse(answer);
		}

		TEST_METHOD(zeroVector)
		{
			double x1 = 1,
				x2 = 3,
				y1 = 1,
				y2 = 3,
				intX = 0,
				intY = 0;

			bool answerTwoPoints = intersect(x1, x1, x2, x2, y1, y1, y2, y2, intX, intY),
				 answertheSamePoints = intersect(x1, x1, x1, x1, y1, y1, y1, y1, intX, intY);
			Assert::IsFalse(answerTwoPoints);
			Assert::IsFalse(answertheSamePoints);
		}

	};
}



